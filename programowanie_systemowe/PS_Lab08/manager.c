// PS IN1 320 LAB08
// Maciej Lewicki
// lm34410@zut.edu.pl
#include "shared.h"

void cleanup()
{
    shm_unlink(shared_mem_name);
    mq_unlink(mq_work_name);
    mq_unlink(mq_return_name);
}

void killAll(pid_t* processes, uint count)
{
    for(uint i=0; i<count; i++)
        if(processes[i]!=0)
        {
            ASSERT_ERROR(kill(processes[i], SIGINT), -1);
            printf("Killing process(%d)", processes[i]);
        }
}

int getIdAndSaltFromHash(char* saltAndHash, char* dest)
{
    uint saltLen = 0;
    char* ptr = strstr(saltAndHash, "$"); // skip first one and find start of salt
    if(!ptr) return 0;
    ptr = strstr(ptr+1, "$"); //second finds start of salt
    if(!ptr) return 0;
    ptr = strstr(ptr+1, "$"); //third finds end of salt
    if(!ptr) return 0;

    saltLen = ptr - saltAndHash;
    memcpy(dest, saltAndHash, saltLen);
    return 1;
}

pid_t* processes;
uint taskCount = 1;

void addProcess(pid_t pid)
{
    for(uint i=0; i<taskCount; i++)
    {
        if(processes[i] == pid)
            break;
        if(processes[i] == 0)
        {
            processes[i] = pid;
            break;
        }
    }
}

void removeProcess(pid_t pid)
{
    for(uint i=0; i<taskCount; i++)
        if(processes[i] == pid)
            processes[i] = 0;
}

void exitHandler(int sig, siginfo_t *info, void* context)
{
    (void)info; (void)context; //not used
    switch (sig) {
    case SIGINT:
        printf("Killing all connected processes, and cleaning up...\n");
        killAll(processes, taskCount);
        cleanup();
        exit(0);
        break;
    }
}


int main(int argc, char **argv)
{
    cleanup(); // this is in case we crashed earlier without cleanup

    // register exitHandler
    struct sigaction sa;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = exitHandler;
    ASSERT_ERROR(sigaction(SIGINT, &sa, NULL), -1);

    int arg;
    int fileHandle = 0;
    int pwFileHandle = 0;

    const char usageMsg[] = "Usage: manager [-t n.o. tasks] encrypted_password dictionary\n";
    while((arg = getopt(argc, argv, "t:")) != -1)
    {
        switch (arg)
        {
        case 't':
            taskCount = atoi(optarg);
            if(taskCount <= 0)
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
    if (optind >= argc) {
        fprintf(stderr, "Missing argument after options.\n");
        fprintf(stderr, usageMsg);
        return 0;
    }

    fileHandle = open(argv[optind+1], O_RDONLY);
    pwFileHandle = open(argv[optind], O_RDONLY);

    if(fileHandle<0 || pwFileHandle<0)
    {
        fprintf(stderr, "Encrypted password and dictionary must be provided.\n");
        fprintf(stderr, usageMsg);
        return 1;
    }


    struct stat fileStatus;
    ASSERT_ERROR(fstat(fileHandle, &fileStatus), -1);

    size_t dictSize = fileStatus.st_size;

    int fd = shm_open(shared_mem_name, O_CREAT | O_EXCL | O_RDWR, 0666);
    ASSERT_ERROR(fd, 0);
    ASSERT_ERROR(ftruncate(fd, sizeof(struct smHeader) +  dictSize), -1);

    char* sharedMem = mmap(0, sizeof(struct smHeader) +  dictSize,
                           PROT_READ | PROT_WRITE,
                           MAP_SHARED, fd, 0);
    ASSERT_ERROR(sharedMem, 0);

    char* file = mmap(0, dictSize, PROT_READ, MAP_PRIVATE, fileHandle, 0);
    ASSERT_ERROR(file, 0);

    // Idk if there is a better way to map this directly to shared mem
    memcpy(sharedMem+sizeof(struct smHeader), file, dictSize);
    munmap(file, dictSize);

    ASSERT_ERROR(fstat(pwFileHandle, &fileStatus), -1);

    struct smHeader* header = (struct smHeader*) sharedMem;
    header->sm_size = sizeof(struct smHeader) +  dictSize;
    ASSERT_ERROR(read(pwFileHandle, header->hash, fileStatus.st_size), -1);

    if(header->hash[fileStatus.st_size-1] == '\n') //overwrite newline if there is one
        header->hash[fileStatus.st_size-1] = 0;

    ASSERT_ERROR(getIdAndSaltFromHash(header->hash, header->saltAndId), 0);

    // split work into jobs
    char* workPtr = sharedMem + sizeof(struct smHeader);
    char* memEnd  = workPtr + dictSize;
    struct WorkDesc jobs[taskCount];
    size_t baseSize = dictSize/taskCount;

    for(uint i=0; i<taskCount; i++)
    {
        jobs[i].offset = workPtr-sharedMem;
        jobs[i].id = i;
        uint size = baseSize;
        if(workPtr+size>memEnd) // if last task
        {
            jobs[i].size = memEnd - workPtr;
            break;
        }
        else
        {
            while(*(workPtr+size)!='\n') //increase the size untill we hit next line
                size++;
            jobs[i].size = size+1;
            workPtr += size+1;
        }
        assert(workPtr<memEnd);
    }

    // create and populate work queue
    struct mq_attr atrib;
    atrib.mq_maxmsg = 10; // this is infuriating
    atrib.mq_msgsize = sizeof (struct WorkDesc);
    mqd_t workQ = mq_open(mq_work_name, O_WRONLY|O_CREAT|O_EXCL, 0666, &atrib);
    ASSERT_ERROR(workQ, -1);

    size_t jobsSubmited = 0;
    for(uint i=0; i<10; i++)
    {
        ASSERT_ERROR(mq_send(workQ, (char*) &jobs[i], sizeof (struct WorkDesc), 1),-1);
        jobsSubmited++;
    }

    // create return queue
    atrib.mq_msgsize = sizeof (struct WorkMsg);
    mqd_t returnQ = mq_open(mq_return_name, O_RDONLY|O_CREAT|O_EXCL, 0666, &atrib);
    ASSERT_ERROR(returnQ, -1);

    uint jobsDone = 0;
    processes = calloc(taskCount, sizeof(pid_t));

    struct WorkMsg msg;
    int nextJobPrio = 1;
    // WorkMsg handling loop
    while(jobsDone < taskCount)
    {
        if(mq_receive(returnQ, (char*)&msg, sizeof (struct WorkMsg),0)>0)
        {
            // handle WorkMsg
            switch (msg.status) {
            case Started:
            {
                printf("Process(%d) withdrew a job(%d).\n", msg.pid, msg.left.id);

                // add pid to list if not already there
                addProcess(msg.pid);

                // submit next job if we didnt do all yet
                if(jobsSubmited<taskCount)
                {
                    printf("Job(%d) submitted.\n", jobs[jobsSubmited].id);
                    ASSERT_ERROR(mq_send(workQ, (char*) &jobs[jobsSubmited], sizeof (struct WorkDesc), nextJobPrio),-1);
                    if(nextJobPrio>1)
                        nextJobPrio = 1;
                    jobsSubmited++;
                }
                break;
            }
            case Finished:
            {
                // if there was a msg we found the pwd otherwise we finished the job but didnt get pwd
                if(strlen(msg.msg)>0)
                {
                    printf("Process(%d) found password: %s in job(%d)\n", msg.pid, msg.msg, msg.left.id);
                    killAll(processes, taskCount);
                    cleanup();
                    return 0;
                }
                else
                {
                    printf("Process(%d) successfuly finished its job(%d)\n", msg.pid, msg.left.id);
                    jobsDone++;
                }
                break;
            }
            case Exit:
            {
                // remove pid from processes list
                removeProcess(msg.pid);
                printf("Process(%d) exited: %s\n", msg.pid, msg.msg);

                if(msg.left.size>0)
                {
                    // resubmit leftover work
                    jobsSubmited--;
                    printf("Returning leftover work as job(%d) with highest priority.\n", msg.left.id);
                    jobs[jobsSubmited] = msg.left;
                    nextJobPrio = 2;
                }
                break;
            }
            }
        }
        else
        {
            LOG_ERR("Failed to get WorkMsg");
        }
    }

    cleanup();
    return 0;
}
