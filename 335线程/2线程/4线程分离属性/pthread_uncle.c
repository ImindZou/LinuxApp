#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define MAX 10000
int number;

void *funA(void* arg)
{
	for(int i=0;i<MAX;i++)
	{
		int ret = number;
		ret++;
		number = ret;
		printf("funA id is %ld,number is %d\n",pthread_self(),number);
		usleep(10);
	}
}

void *funB(void* arg)
{
	for(int i=0;i<MAX;i++)
	{
		int ret = number;
		ret++;
		number = ret;
		printf("funB id is %ld,number is %d\n",pthread_self(),number);
		usleep(10);
	}
}

int main(void)
{
	pthread_t pth1,pth2;
	pthread_create(&pth1,NULL,funA,NULL);
	pthread_create(&pth2,NULL,funB,NULL);

	pthread_join(pth1,NULL);
	pthread_join(pth2,NULL);	

	return 0;
}
