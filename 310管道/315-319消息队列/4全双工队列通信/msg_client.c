#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <unistd.h>


//int msgget(key_t key, int msgflg);
//int msgctl(int msqid, int cmd, struct msqid_ds *buf);
//int msgsnd(int msqid, const void *msgp, size_t msgsz, int msgflg);
/*ssize_t msgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp,
  int msgflg);*/


struct msgbuf{
	long mtype;
	char mtest[128];
	char ID[4];
};

int main()
{
	struct msgbuf sendbuf,readbuf;
	int msgid;
	int readret;
	key_t key;
	pid_t pid;
	key = ftok("a.c",1);
	msgid = msgget(key,IPC_CREAT|0755);
	if(msgid == -1)
	{
		printf("create message queue failed\n");
		return -1;
	}
	system("ipcs -q");
	printf("create message queue sucess msgid = %d\n",msgid);

	//init msgbuf
	sendbuf.mtype = 200;
	pid = fork();
	if(pid == 0)	//child process write 200
	{
		while(1)
		{
			memset(sendbuf.mtest,0,128);
			printf("please input to message queue:\n");
			fgets(sendbuf.mtest,128,stdin);
			msgsnd(msgid,(void *)&sendbuf,strlen(sendbuf.mtest),0);
		}
	}
	if(pid > 0)	//parent process read 100
	{
		while(1)
		{
			memset(readbuf.mtest,0,128);
			msgrcv(msgid,(void *)&readbuf,128,100,0);
			printf("receive byte from message queue is :%s\n",readbuf.mtest);
		}	
	}

	return 0;
	
	}
