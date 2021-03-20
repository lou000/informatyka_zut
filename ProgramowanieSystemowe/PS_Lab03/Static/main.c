// PS IN1 320 LAB03
// Maciej Lewicki
// lm34410@zut.edu.pl

#include <stdlib.h>
#include <utmpx.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <grp.h>
#include <pwd.h>

extern void printUserGroups();

int main(int argc, char **argv)
{
    bool hFlag = false;
    bool gFlag = false;
    int arg;
    while((arg = getopt(argc, argv, "hg")) != -1)
    {
        switch (arg)
        {
        case 'h':
            hFlag = true;
            break;
        case 'g':
            gFlag = true;
            break;
        case '?':
            printf("Invalid argument!\n");
            return 0;
        }
    }

    struct utmpx *utmp;
    setutxent(); //make sure the file pointer is at the start of utmp file
    while((utmp = getutxent())) // get next structure
    {
        if(utmp->ut_type == USER_PROCESS)
        {
            printf("%s  ", utmp->ut_user);
            if(hFlag) printf("(%d)  ",  *utmp->ut_addr_v6); //??? o to chodzi?
            if(gFlag) printUserGroups(utmp->ut_user);
            printf("\n");
        }
    }
    return 0;
}

