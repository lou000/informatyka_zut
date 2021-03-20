// PS IN1 320 LAB02
// Maciej Lewicki
// lm34410@zut.edu.pl

#include <stdlib.h>
#include <utmpx.h>
#include <stdio.h>
#include <stdbool.h>

int main() {

    struct utmpx *utmp;
    setutxent(); //make sure the file pointer is at the start of utmp file
    while((utmp = getutxent())) // get next structure
    {
        if(utmp->ut_type == USER_PROCESS)
            printf("UID %s   LOGIN: %s\n", utmp->ut_id, utmp->ut_user);
    }
    // nie za bardzo wiem po co bylo mi getpwnam
}
