#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

//unsigned int alarm(unsigned int seconds);

int main(void)
{
	int i = 0;
	printf("before alarm\n");
	//alarm(7);
	pause();
	printf("after alarm\n");
	while(i < 20)
	{
		i++;
		sleep(1);
		printf("process %d\n",i);
	}

	return 0;
}
