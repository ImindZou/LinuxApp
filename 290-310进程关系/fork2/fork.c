#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

//pid_t fork(void);
int i = 200;
int main(int argc, char *argv[])
{
	pid_t pid;
	
	pid = fork();
	printf("Nomal i = %d\n",i);

	//father process
	if(pid > 0)
	{
		i += 400;
		printf("This is father process%d\n",getpid());
		printf("father i = %d\n",i);
	}	
	else if(pid == 0)
	{
		i-= 200;
		printf("This is child process %d,ppid is %d\n",getpid(),getppid());
		printf("child i = %d\n",i);
	}

	return 0;
}

