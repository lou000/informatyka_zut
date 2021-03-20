// PS IN1 320 LAB03
// Maciej Lewicki
// lm34410@zut.edu.pl

#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <grp.h>
#include <pwd.h>

void printUserGroups(char* user)
{
    int nGroups = sysconf(_SC_NGROUPS_MAX);
    gid_t groups[nGroups];
    struct passwd* pw = getpwnam(user);
    getgrouplist(pw->pw_name, pw->pw_gid, groups, &nGroups);
    for(int i=0; i<nGroups; i++)
    {
        struct group* gr = getgrgid(groups[i]);
        printf("[%d]%s ",groups[i], gr->gr_name);
    }
}
