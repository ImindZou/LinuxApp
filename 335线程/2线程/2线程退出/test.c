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
	int i,j,k;
	i=10;
	j=20;
	k=30;
	printf("i=%d,j=%d,k=%d\n",i,j,k);
	pthread_testcancel();
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

	int i = 0;
	while(1)
	{
		i++;
		printf("parent i = %d\n",i);
		sleep(1);
	}
	sleep(2);	//线程创建的一个注意事项，就是主线程退出，子线程会被强制结束,所以这里等待了一下。

	pthread_exit(NULL);

	return 0;
}
