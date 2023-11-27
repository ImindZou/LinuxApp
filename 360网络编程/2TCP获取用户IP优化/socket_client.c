/***************CLient 客户端******************/
#include <stdio.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERV_IP 5001
#define SERV_IP_ADDR "192.168.80.131"
#define BACKLOG 5
#define BUFSIZE 1024
#define QUIT_STR "QUIT"


int main(void)
{
	int fd = -1;
	struct sockaddr_in sin;
	
	fd = socket(AF_INET,SOCK_STREAM,0);
	if(fd < 0)
	{
		perror("socket");
		exit(1);
	}
	//初始化字节序
	bzero(&sin,sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(SERV_IP);
	sin.sin_addr.s_addr = inet_addr(SERV_IP_ADDR);

	if(connect(fd,(struct sockaddr*)&sin,sizeof(sin)) < 0)	//链接服务器
	{
		perror("connecte");
		exit(1);
	}
	char buf[BUFSIZE];
	while(1)
	{
		bzero(buf,BUFSIZE);

		if(fgets(buf,BUFSIZE-1,stdin) == NULL)
		{
			continue;
		}

		write(fd,buf,strlen(buf));

		if(!strncasecmp(buf,QUIT_STR,strlen(QUIT_STR)))
		{
			break;
		}
	}

	close(fd);



	return 0;
}
