// PS IN1 320 LAB02
// Maciej Lewicki
// lm34410@zut.edu.pl

#include <stdlib.h>
#include <utmpx.h>
#include <stdio.h>
#include <pwd.h>

int main() {

    struct utmpx *utmp;
    setutxent(); //make sure the file pointer is at the start of utmp file
    while((utmp = getutxent())) // get next structure
    {
        if(utmp->ut_type == USER_PROCESS)
        {
            struct passwd* pw = getpwnam(utmp->ut_user);
            printf("UID %d   LOGIN: %s\n", pw->pw_uid, pw->pw_name);

        }
    }
}
