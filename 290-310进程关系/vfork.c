#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

//pid_t fork(void);


int main()
{
	pid_t pid;
	pid = fork();
	if(pid > 0)
	{
		while(1)
		{
			printf("parent process pid is %d\n",getpid());
			sleep(1);
		}
	}
	else if(pid == 0)
	{
		while(1)
		{
			printf("child process pid is %d\n",getpid());
			sleep(1);
		}
	}

	return 0;
}
