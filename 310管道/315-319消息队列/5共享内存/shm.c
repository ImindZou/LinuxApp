#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <string.h>

//key_t ftok(const char *pathname, int proj_id);
//int shmget(key_t key, size_t size, int shmflg);


int main()
{
	int shmid;
	int key;
	char *p;
	key = ftok("a.c",1);
	if(key < 0)
	{
		printf("ftok failed\n");
		return -2;
	}
	printf("ftok sucess key = %x\n",key);
	shmid = shmget(key,128,IPC_CREAT|0777);
	if(shmid < 0)
	{
		printf("create share memory failed!\n");
		return -1;
	}	
	printf("create share memory sucess shmid = %d\n",shmid);

	system("ipcs -m");

	p = (char *)shmat(shmid,NULL,0);
	if(p == NULL)
	{
		printf("shmat fuction failed!\n");
		return -3;
	}
	//write to share memory 
	fgets(p,128,stdin);
	//read from share memory
	printf("share memory data is %s\n",p);
	printf("second read share memory data is :%s\n",p);

	//shmdt(p);	//将进程里的地址映射删除
	//memcpy(p,"hello world",12);	//删除后数据再读已经是野指针类型了，所以出现段错误
	//shmctl(shmid,IPC_RMID,NULL);
	//system("ipcs -m");
	
	

	return 0;
}
