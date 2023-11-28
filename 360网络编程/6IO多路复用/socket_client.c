/***************CLient 客户端******************/
#include <stdio.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/time.h>


#define SERV_IP 5001
#define SERV_IP_ADDR "192.168.80.131"
#define BACKLOG 5
#define BUFSIZE 1024
#define QUIT_STR "QUIT"
//./client 192.168.80.131 5001

int main(int argc, char **argv[])	//改成参数输入的
{
	int fd = -1;

	if(argc != 3)
	{
		exit(1);
	}
	int port = -1;
	port = atoi(argv[2]);
	
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
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = inet_addr(argv[1]);

	if(connect(fd,(struct sockaddr*)&sin,sizeof(sin)) < 0)	//链接服务器
	{
		perror("connecte");
		exit(1);
	}

	fd_set rset;
	int ret = -1;
	char buf[BUFSIZE];
	int maxfd = -1;
	struct timeval tout;
	while(1)
	{
		FD_ZERO(&rset);
		FD_SET(0,&rset);
		FD_SET(fd,&rset);//依次把i建立好的fd加入到集合中，记录最大文件描述符
		maxfd = fd;

		maxfd = fd;
		tout.tv_sec = 5;
		tout.tv_usec = 0;

		select(maxfd+1,&rset,NULL,NULL,&tout);

		if(FD_ISSET(0,&rset))	//stdin have data
		{
			bzero(buf,BUFSIZE);
			do
			{
				ret = read(0,buf,BUFSIZE-1);
			}while(ret < 0);

			if(ret < 0)
			{
				perror("read");
				continue;
			}
			if(!ret) continue;//no data
			
			if(write(fd,buf,strlen(buf)) < 0)
			{
				perror("write");
				continue;
			}

			if(!strncasecmp(buf,QUIT_STR,strlen(QUIT_STR)))
			{
				printf("client is exited!\n");
				break;
			}
		}
		if(FD_ISSET(fd,&rset))//server have data
		{
			bzero(buf,BUFSIZE);
			do
			{
				ret = read(0,buf,BUFSIZE-1);
			}while(ret < 0);
			if(ret < 0)
			{
				perror("read");
				continue;
			}
			if(!ret<0) break;
			printf("Serve said:%s\n",buf);
			if(!strncasecmp(buf,QUIT_STR,strlen(QUIT_STR)))
			{
				printf("client is exited!\n");
				break;
			}
		}
	}


	close(fd);

	return 0;
}
