#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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
	printf("please input to share memory:\n");
	//write to share memory 
	fgets(p,128,stdin);
	sleep(3);
	shmdt(p);
	//shmctl(shmid,IPC_RMID,0);
	printf("write sucess\n");

	return 0;
}
