#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>

//int semget(key_t key, int nsems, int semflg);

int main(void)
{
	int semid;
	semid = semget(IPC_PRIVATE,3,0755);
	if(semid < 0)
	{
		printf("create semaphore failed\n");
		return -1;
	}
	printf("create semaphore success semid is %d\n",semid);
	system("ipcs -s");

	semctl(semid,0,IPC_RMID,NULL);
	system("ipcs -s");

	return 0;
}
