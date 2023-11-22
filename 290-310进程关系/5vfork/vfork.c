#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

//pid_t fork(void);


int main()
{
	pid_t pid;
	int cnt = 0;
	pid = vfork();
	if(pid > 0)
	{
		while(1)
		{
			printf("cnt is %d\n",cnt);
			printf("parent process pid is %d\n",getpid());
			sleep(1);
		}
	}
	else if(pid == 0)
	{
		while(1)
		{
			cnt++;
			printf("child process pid is %d\n",getpid());
			sleep(1);
			printf("cnt is %d\n",cnt);
			if(cnt == 3)
			{
				exit(0);
			}
		}
	}

	return 0;
}
