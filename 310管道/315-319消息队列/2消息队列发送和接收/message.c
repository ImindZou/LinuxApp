#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

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
	msgid = msgget(IPC_PRIVATE,0755);
	if(msgid == -1)
	{
		printf("create message queue failed\n");
		return -1;
	}
	system("ipcs -q");
	printf("create message queue sucess msgid = %d\n",msgid);

	//init msgbuf
	sendbuf.mtype = 100;
	printf("please input to message queue:\n");
	fgets(sendbuf.mtest,128,stdin);
	//sebd nessage to message queue
	msgsnd(msgid,(void *)&sendbuf,strlen(sendbuf.mtest),0);
	//read
	memset(readbuf.mtest,0,128);
	readret = msgrcv(msgid,(void *)&readbuf,128,100,0);
	printf("message is:%s\n",readbuf.mtest);
	printf("total hava %d byte\n",readret);


	return 0;
}
