#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>

void *myret(void)
{
	return NULL;
}
void *myfunc(void *arg)
{
	printf("child pthread id:%ld\n",pthread_self());
	for(int i=0;i<5;i++)
	{
		printf("child pthread %d\n",i);
		if(i == 2)
		{
			//exit child pthread
			//exit(0);	//用exit会导致所有线程都退出，可以是哟你pthread_exit()来退出单个线程
			//pthread_exit(NULL);
			//return NULL;//也是可以退出的
			myret();
		}
	}
	return 0;
}

int main(void)
{
	pthread_t pthid;
	int ret;
	ret = pthread_create(&pthid,NULL,myfunc,NULL);
	if(ret != 0)
	{
		printf("error number is %d\n",ret);
		printf("%s\n",strerror(ret));
	}
	printf("parent pthread id:%ld\n",pthread_self());

	void* ptr = NULL;

	pthread_join(pthid,&ptr);
	printf("num = %d\n",*(int *)ptr);
	
	int i = 0;
	while(i<10)
	{
		i++;
		printf("parent i = %d\n",i);
		//sleep(1);
	}
	sleep(2);	//线程创建的一个注意事项，就是主线程退出，子线程会被强制结束,所以这里等待了一下。

	pthread_exit(NULL);

	return 0;
}
