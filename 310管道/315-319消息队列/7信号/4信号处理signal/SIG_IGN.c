#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void myfun(int signum)
{
	int i = 0;
	while(i < 10)
	{
		printf("process signum = %d i = %d\n",signum,i);
		sleep(1);
		i++;
	}
}

int main(void)
{
	int i = 0;
	signal(14,myfun);	//14信号等待定时器alarm到时的时候发生信号
	printf("before alarm\n");
	alarm(7);
	printf("before alarm\n");
	signal(14,SIG_IGN);	//如果对信号进行忽略则不会响应相应的闹钟信号
	signal(14,SIG_DFL);	//采用系统默认处理方式则是停止信号
	while(i < 10)
	{
		i++;
		sleep(1);
		printf("process:%d\n",i);
	}
	return 0;
}
