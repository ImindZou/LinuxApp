#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

//int msgget(key_t key, int msgflg);
//int msgctl(int msqid, int cmd, struct msqid_ds *buf);


int main()
{
	int msgid;
	msgid = msgget(IPC_PRIVATE,0755);
	if(msgid == -1)
	{
		printf("create message queue failed\n");
		return -1;
	}
	system("ipcs -q");
	printf("create message queue sucess msgid = %d\n",msgid);
	msgctl(msgid,IPC_RMID,NULL);
	system("ipcs -q");

	return 0;
}
