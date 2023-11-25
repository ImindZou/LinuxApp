#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define MAX 10000
int number;
//create nytes
pthread_mutex_t mutex;

void *funA(void* arg)
{
	for(int i=0;i<MAX;i++)
	{
		//lock
		pthread_mutex_lock(&mutex);//阻塞在此
		int ret = number;
		ret++;
		number = ret;
		printf("funA id is %ld,number is %d\n",pthread_self(),number);
		//unlock
		pthread_mutex_unlock(&mutex);//变量通过系统函数写入到内存后才解锁,放出CPU使用权
		usleep(10);
	}
}

void *funB(void* arg)
{
	for(int i=0;i<MAX;i++)
	{
		//lock
		pthread_mutex_lock(&mutex);//阻塞在此

		int ret = number;
		ret++;
		number = ret;
		printf("funB id is %ld,number is %d\n",pthread_self(),number);
		//unlock
		pthread_mutex_unlock(&mutex);//变量通过系统函数写入到内存后才解锁,放出CPU使用权
		usleep(10);
	}
}

int main(void)
{
	//init mutex
	pthread_mutex_init(&mutex,NULL);
	pthread_t pth1,pth2;
	pthread_create(&pth1,NULL,funA,NULL);
	pthread_create(&pth2,NULL,funB,NULL);

	pthread_join(pth1,NULL);
	pthread_join(pth2,NULL);	

	pthread_mutex_destroy(&mutex);
	return 0;
}
