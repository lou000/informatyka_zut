// PS IN1 320 LAB08
// Maciej Lewicki
// lm34410@zut.edu.pl

#define _GNU_SOURCE
#include "shared.h"
#include <crypt.h>

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

// these need to be global for exitHandler
size_t offset_cashe;
size_t work_count_cashe;
size_t current_job_id;
mqd_t returnQ;

void exitHandler(int sig, siginfo_t *info, void* context)
{
    (void)info; (void)context; //not used
    switch (sig) {
        case SIGINT:
            printf("Exit signal received, sending unfinished work to manager...\n");
            struct WorkMsg msg;
            msg.pid = getpid();
            msg.status = Exit;
            msg.left.offset = offset_cashe;
            msg.left.size = work_count_cashe;
            msg.left.id = current_job_id;
            sprintf(msg.msg, "User interrupted the application.");
            ASSERT_ERROR(mq_send(returnQ, (char*) &msg, sizeof(struct WorkMsg), 1),-1);
            exit(0);
        break;
    }
}

char* attackPassword(char* idAndSalt, char* hash, char* dictionary, uint count, uint maxPwLength)
{
    char* pw = malloc(maxPwLength+1); //this is for performance if there is longer pw in dictionary just skip it
    char* dictPtr = dictionary;
    work_count_cashe = count;
    int printCount = 0;
    while (work_count_cashe>0)
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
                free(pw);
                return NULL;
            }
            if(strcmp(encrypted, hash)==0)
                return pw;
        }
        work_count_cashe -= len+1;
        dictPtr += len+1;
        offset_cashe += len+1;
        printCount++;
        if(printCount % 100 == 0)
            printf("Process %d:  %.2f%%    lastPW: %s\n", getpid(), ((float)(count-work_count_cashe)/(float)count)*100, pw);
    }
    free(pw);
    return NULL;
}

int main(int argc, char **argv)
{
    int arg;
    int jobCount = 1;
    const char usageMsg[] = "Usage: worker [-t n.o. tasks] \n";

    while((arg = getopt(argc, argv, "t:")) != -1)
    {
        switch (arg)
        {
        case 't':
            jobCount = atoi(optarg);
            if(jobCount <= 0)
            {
                fprintf(stderr, "Number of tasks cannot be zero or less.\n");
                fprintf(stderr, usageMsg);
                return 1;
            }
            break;

        case '?':
            fprintf(stderr, usageMsg);
            return 1;
        }
    }


    // the code below expects manager to be running else it will assert
    // it probably should give better error msg then assert

    // open shared memory
    int fd = shm_open(shared_mem_name, O_RDONLY, 0666);
    ASSERT_ERROR(fd, 0);

    // map header, unfortunetly offset has to be divisible by page size
    // so we have to map this memory twice
    struct smHeader* header = mmap(0, sizeof (struct smHeader), PROT_READ,
                                   MAP_SHARED, fd, 0);
    // map whole mem
    char* sharedMem = mmap(0, header->sm_size, PROT_READ,
                           MAP_SHARED, fd, 0);

    // open queues
    mqd_t workQ = mq_open(mq_work_name, O_RDONLY, 0666, 0);
    ASSERT_ERROR(workQ, -1);
    returnQ = mq_open(mq_return_name, O_WRONLY, 0666, 0);
    ASSERT_ERROR(returnQ, -1);

    // register exitHandler
    struct sigaction sa;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = exitHandler;
    ASSERT_ERROR(sigaction(SIGINT, &sa, NULL), -1);


    // job loop
    struct WorkDesc work;
    struct WorkMsg msg;
    msg.pid = getpid();
    for(int i=0; i<jobCount; i++)
    {
        // this below will timeout immiediately, its here so we dont get blocked
        struct timespec timeout;
        clock_gettime(CLOCK_REALTIME, &timeout);
        if(mq_timedreceive(workQ, (char*)&work, sizeof(struct WorkDesc), 0, &timeout)>0)
        {
            // inform manager that we started work
            msg.status = Started;
            msg.left.id = work.id;
            ASSERT_ERROR(mq_send(returnQ, (char*) &msg, sizeof(struct WorkMsg), 1),-1);

            offset_cashe = work.offset;
            current_job_id = work.id;
            char* workMem = sharedMem + work.offset;
            char* pw = attackPassword(header->saltAndId, header->hash, workMem, work.size, MAX_PASS_LEN);

            // inform manager we finished
            msg.status = Finished;
            if(pw)
            {
                strcpy(msg.msg, pw);
                free(pw);
            }
            ASSERT_ERROR(mq_send(returnQ, (char*) &msg, sizeof(struct WorkMsg), 1),-1);
            if(pw)
                return 0;
        }
        else
        {
            fprintf(stderr, "There is no work left in queue.\n");
        }
        printf("Job(%d) finished.\n", work.id);
    }

    msg.status = Exit;
    sprintf(msg.msg, "Application completed all work.");
    msg.left.size = 0;
    ASSERT_ERROR(mq_send(returnQ, (char*) &msg, sizeof(struct WorkMsg), 1),-1);

    return 0;
}
