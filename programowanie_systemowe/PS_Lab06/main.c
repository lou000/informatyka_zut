#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <signal.h>

static pthread_key_t timeStartedKey;
static struct timeval* startTime;

void startTimer()
{
    struct timeval now;
    gettimeofday(&now, NULL);
    startTime = malloc(sizeof(struct timeval));
    *startTime = now;
    pthread_setspecific(timeStartedKey, startTime);
}

void stopTimer()
{
    struct timeval now;
    gettimeofday(&now, NULL);
    pthread_t self = pthread_self();

    struct timeval* specTimeStart = pthread_getspecific(timeStartedKey);
    printf("Start time:%ld \n", specTimeStart->tv_sec*1000 + specTimeStart->tv_usec/1000);
    printf("Thread id:%ld exiting after %ldms \n", self,
           (now.tv_sec*1000 + now.tv_usec/1000) - (specTimeStart->tv_sec*1000 + specTimeStart->tv_usec/1000));
}

static void freeMem(void *buffer)
{
    free(buffer);
}

void* dowork()
{
    startTimer();
    while(1){}
}
void signalHandler(int signum)
{
    if(signum == SIGUSR1)
    {
        stopTimer();
        pthread_exit(NULL);
    }
}

int main(int argc, char **argv)
{
    int arg;
    int numberOfThreads = 2;
    int maxTime  = 10;
    while((arg = getopt(argc, argv, "i:m:")) != -1)
    {
        switch (arg)
        {
        case 'i':
            numberOfThreads = atoi(optarg);
            if(numberOfThreads <= 0)
                fprintf(stderr, "The number of threads argument has to be a number and cannot be zero or negative.\n"
                                "Usage: %s [-n numberOfThreads] [-m maxTime(s)]\n", argv[0]);
            break;
        case 'm':
            maxTime = atoi(optarg);
            if(maxTime <= 0)
                fprintf(stderr, "The number of threads argument has to be a number and cannot be zero or negative.\n"
                                "Usage: %s [-n numberOfThreads] [-m maxTime(s)]\n", argv[0]);
            break;
        case '?':
            fprintf(stderr, "Usage: %s [-n numberOfThreads] [-m maxTime(s)]\n", argv[0]);
            return 0;
        }
    }

    pthread_key_create(&timeStartedKey, freeMem);
    pthread_t* threads = malloc(sizeof(pthread_t) * numberOfThreads);
    int* threadLives = malloc(sizeof(int) * numberOfThreads);

    for(int i=0; i<numberOfThreads; i++)
    {
        int randomLifeTime = rand() % maxTime + 1;
        threadLives[i] = randomLifeTime;
        pthread_create(&threads[i], NULL, dowork, 0);
    }

    int finished = 0;
    struct timeval start, now;
    gettimeofday(&start, NULL);
    signal(SIGUSR1, signalHandler);

    while(finished != numberOfThreads)
    {
        gettimeofday(&now, NULL);
        for(int i=0; i<numberOfThreads; i++)
        {
            if(threads[i] == 0)
                continue;
            int timePassed = now.tv_sec - start.tv_sec;
            if(threadLives[i] <= timePassed)
            {
                if(!pthread_kill(threads[i], SIGUSR1))
                {
                    int result = pthread_join(threads[i], NULL);
                    printf("Thread id:%ld life:%d exited with result %d after %d sec passed.\n\n",
                           threads[i], threadLives[i], result, timePassed);
                    threads[i] = 0;
                    finished++;
                }
            }
        }
    }

    free(threadLives);
    free(threads);
    return 0;
}
