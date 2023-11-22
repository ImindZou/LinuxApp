#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>


//pid_t fork(void);
int i =200;
int main(int argc, char *argv[])
{
	pid_t pid;
	pid = fork();

	//father process
	if(pid > 0)
	{
		int status;
		pid_t wpid;
		while((wpid = waitpid(-1,&status,WNOHANG)) != -1)
		{
			if(wpid == 0)
			{
				continue;
			}
			printf("wpid is %d\n",wpid);
			//nomal exit
			if(WIFEXITED(status))
			{
				printf("exit value is = %d\n",WEXITSTATUS(status));
			}
			if(WIFSIGNALED(status))
			{
				printf("exit by signal =  %d\n",WTERMSIG(status));
			}
			i+=400;
			printf("i=%d\n",i);
			printf("This is father process = %d\n",getpid());
		}
	}	
	//child process
	else if(pid == 0)
	{
		printf("This is child process %d,ppid is %d\n",getpid(),getppid());
	}
	for(int i=0; i<4; i++)
	{
		printf("------i = %d\n",i);
	}	


	return 0;
}

