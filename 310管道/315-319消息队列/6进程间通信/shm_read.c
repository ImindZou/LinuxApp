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
	shmid = shmget(key,128,0);
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
	printf("share memory data:%s\n",p);
	shmdt(p);

	return 0;
}
