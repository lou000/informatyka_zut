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
#include <dlfcn.h>

int main(int argc, char **argv)
{
    void (*printUserGroups)(char*) = 0;
    void* libHandle = dlopen("libGroups.so", RTLD_NOW);
    if(!libHandle)
        printf("Couldnt load lib!\n");
    else{
        dlerror(); //clear
        *(void **) (&printUserGroups) = dlsym(libHandle, "printUserGroups");

        char* error;
        if ((error = dlerror()) != NULL)  {
            printf("Error while loading func from library: %s\n", error);
        }
    }


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
            if(hFlag) printf("(%s)  ",  utmp->ut_host); //??? o to chodzi?
            if(printUserGroups)
                if(gFlag) printUserGroups(utmp->ut_user);
            printf("\n");
        }
    }
    return 0;
}

