#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>


void myfun(int signum)
{
	int i = 0;
	while(i < 5)
	{
		printf("receive signum is %d,i=%d\n",signum,i);
		sleep(1);
		i++;	
	}
}

void myfun1(int signum)
{
	printf("client signal %d sucess\n",signum);
//	wait(NULL);
}

int main(void)
{
	pid_t pid;
	pid = fork();
	if(pid > 0)
	{
		int i = 0;
		signal(10,myfun);
		signal(17,myfun1);
		while(1)
		{
			printf("process i = %d\n",i);
			sleep(1);
			i++;
		}
	}
	if(pid == 0)
	{
		sleep(10);
		kill(getppid(),10);
		sleep(10);
		exit(0);  //kill(getppid(),17);仍是僵尸进程
	}
	
	return 0;
}
