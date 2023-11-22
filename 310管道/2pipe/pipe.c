#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(void)
{

	int ret;
	int fd[2];

	ret = pipe(fd);
	if(ret == -1)
	{
		printf("creat pipe failed\n");
		exit(1);
	}
	pid_t pid = fork();
	if(pid == -1)
	{
		printf("fork failed\n");
		exit(1);
	}
	//ps aux
	if(pid > 0)
	{
		close(fd[0]);
		dup2(fd[1],STDOUT_FILENO);
		execlp("ps","ps","aux",NULL);
		perror("execlp");
		exit(1);
	}
	//grep "bash"
	else if(pid == 0)
	{
		close(fd[1]);
		dup2(fd[0],STDIN_FILENO);
		execlp("grep","grep","bash","--color=auto",NULL);

	}

	printf("pipe[0] is %d\n",fd[0]);
	printf("pipe[0] is %d\n",fd[1]);

	close(fd[0]);
	close(fd[1]);
	return 0;
}
