// PS IN1 320 LAB05
// Maciej Lewicki
// lm34410@zut.edu.pl

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <signal.h>
#include <string.h>
#include <execinfo.h>
#include <wait.h>


int exitReturnVal = 0;
bool userExit = false;
bool childShouldExit = false;
void exit_on_alarm(int sign)
{
    if(sign == SIGALRM)
        childShouldExit = true;
}

void childAndExitHandler(int sig, siginfo_t *info, void* context)
{
    (void) context; //not used
    switch (sig) {
        case SIGCHLD:
        {
        struct timeval current;
        gettimeofday(&current, NULL);
        struct tm* tm_info = localtime(&current.tv_sec);
        char lcTime[] = "(hh:mm:ss)";
        strftime(lcTime, strlen(lcTime)+1, "(%H:%M:%S)", tm_info);
        printf("                                    [%4d]  rand: %2d  %s\n",
               info->si_pid, info->si_status, lcTime);
        }break;
        case SIGINT:
            userExit = true;
        break;
    }

}

int main(int argc, char **argv)
{

    int arg;
    int interval = 2;
    int maxTime  = 10;
    while((arg = getopt(argc, argv, "i:m:")) != -1)
    {
        switch (arg)
        {
        case 'i':
            interval = atoi(optarg);
            if(interval <= 0)
                fprintf(stderr, "The interval argument has to be a number and cannot be zero or negative.\n"
                                "Usage: %s [-i intv(s)] [-m maxTime(s)]\n", argv[0]);
            break;
        case 'm':
            maxTime = atoi(optarg);
            if(maxTime <= 0)
                fprintf(stderr, "The maxTime argument has to be a number and cannot be zero or negative.\n"
                                "Usage: %s [-i intv(s)] [-m maxTime(s)]\n", argv[0]);
            break;
        case '?':
            fprintf(stderr, "Usage: %s [-i intv(s)] [-m maxTime(s)]\n", argv[0]);
            return 0;
        }
    }

    struct sigaction sa;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = childAndExitHandler;
    sigaction(SIGCHLD, &sa, NULL);
    sigaction(SIGINT, &sa, NULL);

    struct timeval start, now;
    gettimeofday(&start, NULL);
    while(true)
    {
        pid_t forkPid;
        gettimeofday(&now, NULL);
        int tPassed = (now.tv_sec - start.tv_sec);
        if(tPassed >= interval && !userExit) // do only when enough time has passed and user didnt exit
        {
            forkPid = fork();
            if (forkPid == 0) // fork stuff
            {
                srand(now.tv_sec); // we have to seed it because it would be the same everytime
                exitReturnVal = rand() % maxTime + 1;
                struct tm* tm_info = localtime(&now.tv_sec);
                char lcTime[] = "(hh:mm:ss)";
                strftime(lcTime, strlen(lcTime)+1, "(%H:%M:%S)", tm_info);
                printf("[%4d]  rand: %2d  %s\n",
                       getpid(), exitReturnVal, lcTime);

                signal(SIGALRM, exit_on_alarm);
                alarm(exitReturnVal);

                //some "work"
                int cnt = 1;
                unsigned long long factorial = 1;
                while(!childShouldExit) //this global is set in exit_on_alarm
                {
                    factorial*=cnt;
                    cnt++;
                }
                exit(exitReturnVal);
            }
            gettimeofday(&start, NULL);
        }
        if(userExit) // this is set in childAndExitHandler
        {
            int status = 0;
            while(wait(&status)>0);
            exit(0);
        }
    }
}
