#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

//pid_t fork(void);

int main(int argc, char *argv[])
{
	pid_t pid;
	
	pid = fork();

	for(int i=0;i<4;i++)
	{
		printf("************i=%d\n",i);
	}
	//father process
	if(pid > 0)
	{
		printf("This is father process%d\n",getpid());
	}	
	else if(pid == 0)
	{
		printf("This is child process %d,ppid is %d\n",getpid(),getppid());
	}
	for(int i=0; i<4; i++)
	{
		printf("i = %d\n",i);
	}	


	return 0;
}

