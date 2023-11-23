#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>


int main()
{
	/*printf("before sig\n");	//这里有一个魔鬼细节，就是用户太到内核态的一个过程，需要一个换行符，或者字节达到一定数量,才可以打印此进程，不然没进入内核态是无法打印的
	raise(9);
	printf("after sig\n");*/
	pid_t pid;
	pid = fork();
	if(pid > 0)
	{
		sleep(8);
		if(waitpid(pid,NULL,WNOHANG) == 0)
		{
			kill(pid,9);	//杀死子进程
		}
		wait(NULL);	//回收子进程残留资源
		while(1);
	}
	if(pid == 0)
	{
		printf("before sig\n");
		raise(SIGTSTP);
		printf("after sig\n");
	}

	return 0;
}
