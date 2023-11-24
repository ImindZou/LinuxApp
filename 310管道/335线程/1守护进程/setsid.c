#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>


/*说明：
 *守护进程创建后独立于控制终端
 *可以周期性执行任务
 *不受哟农户登录注销影响
 *
 * 创建会话注意事项：
 * 不可能是进程组长
 * 创建绘画的进程成为新进程组的组长
 * 创建新的会话会丢失原有的控制终端
 * 一般步骤，父子进程中的父进程死掉，子进程调用setsid()创建一个会话，这是独有的守护进程，他的状态是Rs/可能是Reserve的意思吧，守护/
 * 还可以获取该进程的ID（getsid()）
 * */

int main(void)
{
	pid_t pid;
	pid = fork();
	if(pid > 0)
	{
		exit(1);
		//kill(getpid(),SIGKILL);
		//raise(SIGKILL);
	}
	else if(pid == 0)
	{
		setsid();
		printf("the Ps ID is %d\n",getsid(pid));

		while(1);
	}


	return 0;
}
