#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <unistd.h>


#define SEM_READ 0
#define SEM_WRITE 0

//int semop(int semid, struct sembuf *sops, size_t nsops);//第三个为信号量个数

//信号灯的PV操作可以理解为对该进程进行控制操作与释放内存

void Poperation(int index,int semid)
{
	struct sembuf sop;

	sop.sem_num = index;
	sop.sem_op = -1;
	sop.sem_flg = 0;

	semop(semid,&sop,1);	//第二个取信号操作结构体的属性
}

void Voperation(int index,int semid)
{
	struct sembuf sop;

	sop.sem_num = index;
	sop.sem_op = 1;
	sop.sem_flg = 0;

	semop(semid,&sop,1);
}

union semun
{
	int val;
};

int main(void)
{
	key_t key;
	key = ftok(".",123);

	int semid;
	int shmid;
	char *shmaddr;
	pid_t pid;
	semid = semget(key,2,IPC_CREAT|0755);	//两个信号直，分别读写
	if(semid < 0)
	{
		perror("semget");
		return -1;
	}
	shmid = shmget(key,128,IPC_CREAT|0755);
	if(shmid < 0)
	{
		perror("shmget");
		return -2;
	}

	//init semaphore 
	union semun myun;
	//init semaphore read 
	myun.val = 0;
	semctl(semid,SEM_READ,SETVAL,myun);
	//init semaphore write 
	myun.val = 1;
	semctl(semid,SEM_WRITE,SETVAL,myun);

	pid = fork();
	if(pid == 0)//child process
	{
		while(1)
		{
			shmaddr = (char *)shmat(shmid,NULL,0);

			Poperation(SEM_READ,semid);	//这里的P和V操作保证了读的时候只能读，写的时候只能写，这是原子操作的概念
			printf("get share memory is :%s\n",shmaddr);
			Voperation(SEM_WRITE,semid);
		}
	}
	else if(pid > 0)//parent process
	{
		while(1)
		{
			shmaddr = (char *)shmat(shmid,NULL,0);

			Poperation(SEM_WRITE,semid);
			printf("please input to share memory\n");
			fgets(shmaddr,32,stdin);
			Voperation(SEM_READ,semid);
		}	
	}

	return 0;
}
