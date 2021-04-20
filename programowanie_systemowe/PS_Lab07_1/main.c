#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <crypt.h>

int main(int argc, char **argv)
{
    int arg;
    char* password = NULL;
    char* salt = NULL;
    while((arg = getopt(argc, argv, "p:s:")) != -1)
    {
        switch (arg)
        {
        case 'p':
            if(strlen(optarg) == 0)
            {
                fprintf(stderr, "Provide a password.\n"
                                "Usage: %s [-p password] [-s salt]\n", argv[0]);
                return 1;
            }
            else
            {
                password = optarg;
            }
            break;
        case 's':
            if(strlen(optarg) <= 0 || strlen(optarg)>16)
            {
                fprintf(stderr, "Provide salt that is up to 16 characters long.\n"
                                "Usage: %s [-n numberOfThreads] [-m maxTime(s)]\n", argv[0]);
                return 1;
            }
            else
            {
                salt = optarg;
            }
            break;
        case '?':
            fprintf(stderr, "Usage: %s [-p password] [-s salt]\n", argv[0]);
            return 1;
        }
    }
    if(!password || !salt)
    {
        fprintf(stderr, "Both arguments are required.\n Usage: %s [-p password] [-s salt]\n", argv[0]);
        return 1;
    }
    char* idAndSalt = malloc(strlen(salt)+3);
    strcpy(idAndSalt, "$6$");
    strncat(idAndSalt, salt, strlen(salt));

    char* encrypted = crypt(password, idAndSalt);
    printf("%s\n", encrypted);
    free(idAndSalt);
    return 0;
}
