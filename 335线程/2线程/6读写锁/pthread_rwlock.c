#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int number = 10000;
//create rwlock

pthread_rwlock_t lock;

void *write_func(void *arg)
{
	while(1)
	{
		pthread_rwlock_wrlock(&lock);
		number++;
		printf("write id :%ld,number = %d\n",pthread_self(),number);
		pthread_rwlock_unlock(&lock);
		usleep(500);
	}
}

void *read_func(void *arg)
{
	while(1)
	{
		pthread_rwlock_rdlock(&lock);
		printf("read id :%ld,number = %d\n",pthread_self(),number);
		pthread_rwlock_unlock(&lock);
		usleep(500);
	}
}

int main(void)
{
	//rwlock init
	pthread_rwlock_init(&lock,NULL);
	pthread_t p[8];//还有一个主线程要算进去
	for(int i=0;i<3;++i)
	{
		pthread_create(&p[i],NULL,write_func,NULL);
	}
	for(int i=3;i<8;++i)
	{
		pthread_create(&p[i],NULL,read_func,NULL);
	}

	for(int i=0;i<8;++i)
	{
		pthread_join(p[i],NULL);
	}

	pthread_rwlock_destroy(&lock);

	return 0;
}
