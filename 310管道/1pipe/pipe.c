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

	printf("pipe[0] is %d\n",fd[0]);
	printf("pipe[0] is %d\n",fd[1]);

	close(fd[0]);
	close(fd[1]);
	return 0;
}
