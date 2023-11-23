#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>



int main(void)
{
	int i = 0;
	printf("before alarm\n");
	alarm(7);
	printf("after alarm\n");
	while(i < 10)
	{
		i++;
		sleep(1);
		printf("process:%d\n",i);
	}
	return 0;
}
