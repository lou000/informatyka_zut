// PS IN1 320 LAB07
// Maciej Lewicki
// lm34410@zut.edu.pl

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
    uint chars = 0;
    while (chars<count)
    {
        uint len = lineLen(dictPtr);
        if(len<maxPwLength)
        {
            struct crypt_data data;
            memcpy(pw, dictPtr, len+1); // +1 for '\0'
            pw[len] = 0;

            char* encrypted = crypt_r(pw, idAndSalt, &data);
            if(!encrypted)
            {
                fprintf(stderr, "Failed to encrypt password according to your password format.\n");
                return NULL;
            }
            if(strcmp(encrypted, hash)==0)
                return pw;
        }
        chars += len+1;
        dictPtr += len+1;
        if(chars % 2000 == 0)
            printf("Thread nr %ld:  %.2f%%    lastPW: %s\n", pthread_self(), ((float)chars/(float)count)*100, pw);
    }
    free(pw);
    return NULL;
}

struct workInfo{
    char* idAndSalt;
    char* hash;
    char* dictionary;
    uint dictSize;
    uint maxPwLength;
};

void* threadWork(void* workInfo)
{
    struct workInfo* info = (struct workInfo*) workInfo;
    char* pw = attackPassword(info->idAndSalt, info->hash,
                              info->dictionary, info->dictSize,
                              info->maxPwLength);
    pthread_exit(pw);
}

int runThreadCreationLoop(uint threadCount, struct workInfo info)
{
    char* file = info.dictionary;
    char* encryptedPassword = info.hash;
    char* idAndSalt = info.idAndSalt;
    uint maxPwLength = info.maxPwLength;
    uint dictSize = info.dictSize;

    pthread_t* threads = malloc(sizeof(pthread_t) * threadCount);
    struct workInfo* infoArray = malloc(sizeof (struct workInfo) * threadCount);
    for(uint i=0; i<threadCount; i++)
    {
        if(i == threadCount - 1) //last thread gets the remaining bit
            infoArray[i].dictSize = (dictSize/threadCount)+dictSize % threadCount;
        else
            infoArray[i].dictSize = dictSize/threadCount;

        infoArray[i].dictionary = file;
        infoArray[i].hash = encryptedPassword;
        infoArray[i].idAndSalt = idAndSalt;
        infoArray[i].maxPwLength = maxPwLength;
        pthread_create(&threads[i], NULL, threadWork, (void*)(infoArray+i));
        file+=dictSize/threadCount;
    }

    uint finished = 0;
    while(finished != threadCount)
    {
        for(uint i=0; i<threadCount; i++)
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
                    free(threads);
                    free(infoArray);
                    return 1;
                }
                threads[i] = 0;
                finished++;
            }
        }
    }
    free(threads);
    free(infoArray);
    return 0;
}


int main(int argc, char **argv)
{
    int arg;
    int fileHandle = 0;
    int pwFileHandle = 0;
    uint maxPwLength = 200;
    uint maxThreads = 0;
    while((arg = getopt(argc, argv, "m:t:")) != -1)
    {
        //FIXME: hash and dictionary shouldnt be optional
        switch (arg)
        {
        case 'm':
            maxPwLength = atoi(optarg);
            if(maxPwLength <= 0)
                fprintf(stderr, "Max pw length cannot be zero or less.\n"
                                "Usage: Lab07_1 [-m max pw length] [-t n.o. threds] encrypted_password dictionary\n");
            break;
        case 't':
            maxThreads = atoi(optarg);
            if(maxThreads <= 0)
                fprintf(stderr, "Max threads cannot be zero or less.\n"
                                "Usage: Lab07_1 [-m max pw length] [-t n.o. threds] encrypted_password dictionary\n");
            break;


        case '?':
            fprintf(stderr, "Usage: Lab07_1 [-m max pw length] [-t n.o. threds] encrypted_password dictionary\n");
            return 1;
        }
    }
    if (optind >= argc) {
        fprintf(stderr, "Missing argument after options.\n");
        fprintf(stderr, "Usage: Lab07_1 [-m max pw length] [-t n.o. threds] encrypted_password dictionary\n");
        return 0;
    }

    fileHandle = open(argv[optind+1], O_RDONLY);
    pwFileHandle = open(argv[optind], O_RDONLY);

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

    success = fstat(pwFileHandle, &fileStatus);
    if(success<0)
    {
        fprintf(stderr, "Couldnt get the length of dictionary file, exiting.\n");
        return 1;
    }
    char* encryptedPassword = malloc(fileStatus.st_size);
    if(read(pwFileHandle, encryptedPassword, fileStatus.st_size)==-1)
    {
        fprintf(stderr, "Couldnt read encypted password from file.\n");
        return 1;
    }
    if(encryptedPassword[fileStatus.st_size-1] == '\n') //overwrite newline if there is one
        encryptedPassword[fileStatus.st_size-1] = 0;


    char* idAndSalt = getIdAndSaltFromHash(encryptedPassword);

    if(!idAndSalt)
    {
        fprintf(stderr, "Failed to find salt in hash, exiting.\n");
        return 1;
    }


    struct workInfo info;
    info.dictSize = dictSize;
    info.dictionary = file;
    info.hash = encryptedPassword;
    info.idAndSalt = idAndSalt;
    info.maxPwLength = maxPwLength;

    if(maxThreads == 0)
    {
        // do the perf testing here
        info.dictSize = 2000;
        info.hash = "dummyHash";
        printf("Max threads not specified, running performance test to determine optimal number of threads.\n");
        for(uint i=1; i<=10; i++) //testing up to ten threads
        {
            struct timespec time1, time2;
            clock_gettime(CLOCK_MONOTONIC, &time1);
            runThreadCreationLoop(i, info);
            clock_gettime(CLOCK_MONOTONIC, &time2);
            double diffClock = (time2.tv_sec - time1.tv_sec) * 1000 + (double)(time2.tv_nsec - time1.tv_nsec) * 1e-6;
            printf("%d thread(s): %.3fms\n", i, diffClock);
        }
    }
    else
        runThreadCreationLoop(maxThreads, info);

    free(encryptedPassword);
    free(idAndSalt);
    return 0;
}
