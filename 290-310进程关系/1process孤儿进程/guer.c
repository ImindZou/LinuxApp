#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

//pid_t fork(void);


int main(int argc, char *argv[])
{
	pid_t pid;
	pid = fork();
	if(pid == 0)
	{
		sleep(2);
		printf("child process pid %d ppid %d\n",getpid(),getppid());
	}
	else if(pid > 0)
	{
		printf("parent process pid %d ppid %d\n",getpid(),getppid());
	}

	return 0;
}
