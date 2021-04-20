#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <pthread.h>
#include <crypt.h>


char* skipNLines(char* file, uint count)
{
    uint lines = 0;
    while(lines<count)
    {
        while(file[0] != '\n')
            file++;
        file++;
        lines++;
    }
    return file;
}

uint lineLen(char* filePtr)
{
    uint count = 0;
    while(filePtr[0] != '\n')
    {
        filePtr++;
        count++;
    }
    return count;
}

char* getIdAndSaltFromHash(char* saltAndHash)
{
    uint saltLen = 0;
    char* ptr = strstr(saltAndHash, "$"); // skip first one and find start of salt
    if(!ptr) return 0;
    ptr = strstr(ptr+1, "$"); //second finds start of salt
    if(!ptr) return 0;
    ptr = strstr(ptr+1, "$"); //third finds end of salt
    if(!ptr) return 0;

    saltLen = ptr - saltAndHash;
    char* salt = malloc(saltLen);
    memcpy(salt, saltAndHash, saltLen);
    return salt;
}

char* attackPassword(char* idAndSalt, char* hash, char* dictionary, uint count, uint maxPwLength)
{
    char* pw = malloc(maxPwLength+1); //this is for performance if there is longer pw in dictionary just skip it
    char* dictPtr = dictionary;
    uint lines = 0;
    while (lines<count)
    {
        uint len = lineLen(dictPtr);
        if(len<maxPwLength)
        {
            struct crypt_data data;
            memcpy(pw, dictPtr, len+1); // +1 for '\0'
            pw[len] = 0;

            char* encrypted = crypt_r(pw, idAndSalt, &data);
            if(strcmp(encrypted, hash)==0)
                return pw;
        }
        lines++;
        dictPtr+=len+1;
        if(lines % 1000 == 0)
            printf("Thread nr %ld:  %.2f%%    lastPW: %s\n", pthread_self(), ((float)lines/(float)count)*100, pw);
    }
    free(pw);
    return NULL;
}

struct workInfo{
    char* idAndSalt;
    char* hash;
    char* dictionary;
    uint count;
    uint maxPwLength;
};

void* threadWork(void* workInfo)
{
    struct workInfo* info = (struct workInfo*) workInfo;
    char* pw = attackPassword(info->idAndSalt, info->hash,
                              info->dictionary, info->count,
                              info->maxPwLength);
    pthread_exit(pw);
}


int main(int argc, char **argv)
{
    int arg;
    int fileHandle = 0;
    int pwFileHandle = 0;
    uint maxPwLength = 200;
    uint maxThreads = 0;
    while((arg = getopt(argc, argv, "e:d:m:t:")) != -1)
    {
        //FIXME: hash and dictionary shouldnt be optional
        switch (arg)
        {
        case 'e':
            if((pwFileHandle = open(optarg, O_RDONLY))<0)
            {
                fprintf(stderr, "Couldnt open file with encrypted password.\n"
                                "Usage: Lab07_1 [-e encypted pw file] [-d dictionary file] [-m max pw length] [-t n.o. threds]\n");
                return 1;
            }
            break;
        case 'd':
            if((fileHandle = open(optarg, O_RDONLY))<0)
            {
                fprintf(stderr, "Couldnt open provided dictionary file.\n"
                                "Usage: Lab07_1 [-e encrypted pw] [-d dictionary file] [-m max pw length] [-t n.o. threds]\n");
                return 1;
            }
            break;
        case 'm':
            maxPwLength = atoi(optarg);
            if(maxPwLength <= 0)
                fprintf(stderr, "Max pw length cannot be zero or less.\n"
                                "Usage: Lab07_1 [-e encrypted pw] [-d dictionary file] [-m max pw length] [-t n.o. threds]\n");
            break;
        case 't':
            maxThreads = atoi(optarg);
            if(maxThreads <= 0)
                fprintf(stderr, "Max threads cannot be zero or less.\n"
                                "Usage: Lab07_1 [-e encrypted pw] [-d dictionary file] [-m max pw length] [-t n.o. threds]\n");
            break;


        case '?':
            fprintf(stderr, "Usage: Lab07_1 [-e encrypted pw] [-d dictionary file] [-m max pw length] [-t n.o. threds]\n");
            return 1;
        }
    }
    if(fileHandle<0 || pwFileHandle<0)
        fprintf(stderr, "Encrypted password and dictionary must be provided.\n"
                        "Usage: Lab07_1 [-e encrypted pw] [-d dictionary file] [-m max pw length] [-t n.o. threds]\n");

    struct stat fileStatus;
    int success = 0;
    success = fstat(fileHandle, &fileStatus);
    if(success<0)
    {
        fprintf(stderr, "Couldnt get the length of dictionary file, exiting.\n");
        return 1;
    }
    size_t dictSize = fileStatus.st_size;
    char* file = mmap(0, dictSize, PROT_READ, MAP_PRIVATE, fileHandle, 0);
    if(!file)
    {
        fprintf(stderr, "Failed to map the file, exiting.\n");
        return 1;
    }
    char* fileEnd = file+fileStatus.st_size;
    char* fileStart = file;

    success = fstat(pwFileHandle, &fileStatus);
    if(success<0)
    {
        fprintf(stderr, "Couldnt get the length of dictionary file, exiting.\n");
        return 1;
    }
    char* encryptedPassword = malloc(fileStatus.st_size);
    read(pwFileHandle, encryptedPassword, fileStatus.st_size);
    if(encryptedPassword[fileStatus.st_size-1] == '\n') //overwrite newline if there is one
        encryptedPassword[fileStatus.st_size-1] = 0;


    char* idAndSalt = getIdAndSaltFromHash(encryptedPassword);

    if(!idAndSalt)
    {
        fprintf(stderr, "Failed to find salt in hash, exiting.\n");
        return 1;
    }

    if(maxThreads == 0)
    {
        maxThreads = sysconf(_SC_NPROCESSORS_ONLN);
        printf("Max threads not specified using %d threads as default.\n", maxThreads);
    }

    pthread_t* threads = malloc(sizeof(pthread_t) * maxThreads);
    struct workInfo* info = malloc(sizeof (struct workInfo) * maxThreads);
    for(uint i=0; i<maxThreads && file<fileEnd; i++)
    {
        info[i].count = dictSize/maxThreads;
        info[i].dictionary = file;
        info[i].hash = encryptedPassword;
        info[i].idAndSalt = idAndSalt;
        info[i].maxPwLength = maxPwLength;
        pthread_create(&threads[i], NULL, threadWork, (void*)(info+i));
        file+=dictSize/maxThreads;
    }
    // need to do rest of the file when we encounter end

    uint finished = 0;
    while(file<=fileEnd)
    {
        for(uint i=0; i<maxThreads; i++)
        {
            if(threads[i] == 0)
                continue;
            char* retVal;
            int result = pthread_join(threads[i], (void**)&retVal);
            if(!result) // thread exited
            {
                if(retVal)
                {
                    printf("Found the password: %s\n", retVal);
                    return 0;
                }
//                else
//                {
//                    float progress = (float)(file - fileStart)/(float)(fileEnd-fileStart);
//                    printf("Progress: %.3f%%\n", progress);
//                    pthread_create(&threads[i], NULL, threadWork, (void*)(info+i));
//                    file+=1000;
//                }
                threads[i] = 0;
                finished++;
            }
        }
    }

    free(idAndSalt);
    free(info);
    free(threads);
}
