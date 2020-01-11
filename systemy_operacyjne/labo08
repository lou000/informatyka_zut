#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int main(int argc, char* argv[])
{
	if(argc!=2)
	{
		fprintf(stderr, "Podano %d, argumentów.\n", argc-1);
		return -1;
	}
	if(strlen(argv[1])<2)
	{
		return *argv[1];
	}

	int len = strlen(argv[1]);
	int middle = len/2;
	char* split1 = argv[1];
	char* split2 = malloc(sizeof(char)*(middle+1));
	char * arr[] = {split1, split2};
	memcpy(split2, split1+middle, sizeof(char)*(middle+1));
	split1[middle] = '\0';
	int pid1;
	int pid2;
	int pidP=getpid();
	int status;

	pid1 = fork();
	if(pid1==0)
	{
		char * arg[] = {split2, split1, NULL};
		if(execvp("/home/lewy/Documents/34410.so.lab08", arg)<0)
			printf("error: %d\n", errno);
	}
	else{
		pid2 = fork();
		if(pid2==0)
		{
			pid2 = getpid(); 
			char * arg[] = {split1, split2, NULL};
		if(execvp("/home/lewy/Documents/34410.so.lab08", arg)<0)
			printf("error: %d\n", errno);
		}
		else{
			int gStatus=1;
			int pid;
			int i=0;
			while((pid = wait(&status)) > 0)
			{
				int ret=0;
				if(WIFEXITED(status))
					ret = WEXITSTATUS(status);
				if(pid==pid1)
					printf("Rodzic: %d, Dziecko: %d, arg: %s, kod_zakończenia: %c\n",
							pidP, pid, arr[0], ret);
				else if(pid==pid2)
					printf("Rodzic: %d, Dziecko: %d, arg: %s, kod_zakończenia: %c\n",
							pidP, pid, arr[1], ret);
				if(ret>gStatus)
					gStatus = ret;
				i++;
			}
			return gStatus;
		}
	}
}
