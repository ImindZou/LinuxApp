#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>

//int kill(pid_t pid, int sig);

int main(int argc,char *argv[])
{
	int sig,pid;
	if(argc < 3)
	{
		printf("input error!\n");
		return -1;
	}

	sig = atoi(argv[1]);
	pid = atoi(argv[2]);
	printf("sig = %d,pid = %d\n",sig,pid);
	kill(pid,sig);


	return 0;
}
