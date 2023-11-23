#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <string.h>


int main(int argc,char *argv[])
{
	int shmid;
	if(argc < 3)
	{
		printf("input error\n");
		return -1;
	}
	if(strcmp(argv[1],"-m") == 0)
	{
		printf("delete share memory\n");
	}
	else
	{
		return -2;
	}
	shmid = atoi(argv[2]);
	printf("delete share memory id:%d\n",shmid);
	shmctl(shmid,IPC_RMID,NULL);
	system("ipcs -m");

	return 0;
}
