#include <stdio.h>
#include <pthread.h>
#include <string.h>

void *myfunc(void *arg)
{
	printf("child pthread id:%ld\n",pthread_self());
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

	for(int i=0;i<5;i++)
	{
		printf("i = %d\n",i);
	}
	sleep(2);	//线程创建的一个注意事项，就是主线程退出，子线程会被强制结束,所以这里等待了一下。

	return 0;
}
