// PS IN1 320 LAB06
// Maciej Lewicki
// lm34410@zut.edu.pl
#include "timer.h"

void startTimer()
{
    struct timeval now;
    gettimeofday(&now, NULL);
    if(!pthread_getspecific(timeStartedKey))
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
    if(specTimeStart)
        printf("Thread id:%ld exiting after %ldms \n", self,
            (now.tv_sec*1000 + now.tv_usec/1000) - (specTimeStart->tv_sec*1000 + specTimeStart->tv_usec/1000));
}
