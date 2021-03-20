#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <time.h>
#include <fcntl.h>


int main(int argc, char **argv)
{
    int arg;
    bool vFlag = false;
    int repeats = 1;
    while((arg = getopt(argc, argv, "vt:")) != -1)
    {
        switch (arg)
        {
        case 'v':
            vFlag = true;
            break;
        case 't':
            repeats = atoi(optarg);
            if(repeats == 0)
                fprintf(stderr, "The nreps argument has to be a number and cannot be 0.\n"
"                                Usage: %s [-t nreps] [-v] application\n",
                                           argv[0]);
            break;
        case '?':
            fprintf(stderr, "Usage: %s [-t nreps] [-v] application\n",
                                       argv[0]);
            return 0;
        }
    }
    if (optind >= argc) {
        fprintf(stderr, "Missing argument after options.\n");
        fprintf(stderr, "Usage: %s [-t nreps] [-v] application\n",
                                   argv[0]);
        return 0;
    }



    char* appName = argv[optind];
    fprintf(stdout, "\nMeasuring time[ms]: %s ", argv[optind]);
    char* appArgs[argc - optind];
    for(int i=optind, j=0; i<argc; i++, j++)
    {
        if(i != optind)
            fprintf(stdout, "%s ", argv[i]);
        appArgs[j] = argv[i];
    }
    fprintf(stdout, "\n===================================\n");

    struct rusage usg;
    int status = 1;
    int oPid = getpid();
    int fPid = -1;
    double aggTimeClock = 0;
    double aggTimeUser  = 0;
    double aggTimeSys   = 0;

    fprintf(stdout, "Run   clock_gettime   user   system \n");
    for(int i=1; i<=repeats; i++)
    {

        if(getpid() == oPid)
            fPid = fork();

        if (fPid == 0)
        {
            int null;
            if(!vFlag)
            {
                null = open("/dev/null", O_WRONLY);
                dup2(null, STDOUT_FILENO);
                dup2(null, STDERR_FILENO);
            }
            if(execvp(appName, appArgs) == -1)
                fprintf(stderr, "The command '%s' failed to run.\n", argv[optind]);
            if(!vFlag && null>0)
            {
                close(null);
                close(null);
            }
            _exit(0);
        }
        else
        {
            struct timespec time1, time2;
            clock_gettime(CLOCK_MONOTONIC, &time1);
            wait4(fPid, &status, 0, &usg);
//            printf("Child PID: %d   Result: %d\n",fPid, WEXITSTATUS(status));
            clock_gettime(CLOCK_MONOTONIC, &time2);
            double diffClock = (time2.tv_sec - time1.tv_sec) * 1000 + (double)(time2.tv_nsec - time1.tv_nsec) * 1e-6;
            double diffUser  = usg.ru_utime.tv_sec * 1000 + (double)usg.ru_utime.tv_usec * 0.001f;
            double diffSys   = usg.ru_stime.tv_sec * 1000 + (double)usg.ru_stime.tv_usec * 0.001f;

            aggTimeClock += diffClock;
            aggTimeUser  += diffUser;
            aggTimeSys   += diffSys;
            fprintf(stdout, "%-8d %6.3f %10.3f %8.3f\n", i, diffClock, diffUser, diffSys);
        }
    }
    fprintf(stdout, "===================================\n");
    fprintf(stdout, "Avg      %6.3f %10.3f %8.3f\n",
           aggTimeClock/repeats, aggTimeUser/repeats, aggTimeSys/repeats);

    return 0;
}

