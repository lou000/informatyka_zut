// PS IN1 320 LAB06
// Maciej Lewicki
// lm34410@zut.edu.pl
#ifndef TIMER_H
#define TIMER_H
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#include <signal.h>

static pthread_key_t timeStartedKey;
static struct timeval* startTime;

void startTimer();
void stopTimer();

#endif // TIMER_H
