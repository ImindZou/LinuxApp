/***********Serve 服务端****************/
#include <stdio.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>                                                                                           


#define SERV_IP 5001
#define SERV_IP_ADDR "192.168.80.131"
#define BACKLOG 5
#define BUFSIZE 1024
#define QUIT_STR "QUIT"

void *client_data_handle(void* arg);

int main(void)
{
	int fd = -1;
	struct sockaddr_in sin;

	//1创建套接字
	fd = socket(AF_INET,SOCK_STREAM,0);
	if(fd < 0)
	{
		perror("socket");
		exit(1);
	}
	//转换字节序   本地---》网络	
	bzero(&sin,sizeof(sin));
	sin.sin_family = AF_INET;	//IPv4
	sin.sin_port = htons(SERV_IP);	//端口配置5001
					//sin.sin_addr.s_addr = inet_addr(SERV_IP_ADDR);	//IP地址配置

					//----------------------------》》优化1,自动查询ipv4地址
	sin.sin_addr.s_addr = INADDR_ANY;
	/*此函数相当于上面的一系列结构体属性配置，直接宏定义来的更方便
	 * if(inet_pton(AF_INET,SERV_IP_ADDR,(void *)&sin.sin_addr.s_addr) != 1)
	 {
	 perror("inet_pton");
	 exit(1);
	 }
	 */

	//2绑定流式套接字
	if(bind(fd,(struct sockaddr *)&sin,sizeof(sin)) < 0)
	{
		perror("bind");
		exit(1);
	}

	//3listen()	从主动监听到被动接收的一个过程
	if(listen(fd,BACKLOG) < 0)
	{
		perror("listen");
		exit(1);
	}

	//4accept()
	/*
	   int newfd = -1;
	   newfd = accept(fd,NULL,NULL);
	   if(newfd < 0)
	   {
	   perror("accept");
	   exit(1);
	   }
	   */
	//------------------------------》》优化2,在接收客户端信息的同时接收客户端IP信息
	//思路：网络字节序-----------》》本地字节序
	//1创建多线程
	pthread_t tid;
	
	int newfd = -1;
	struct sockaddr_in cin;
	socklen_t addrlen = sizeof(cin);
	while(1)
	{
		newfd = accept(fd,(struct sockaddr *)&cin,&addrlen);
		if(newfd < 0)
		{
			perror("accept");
			exit(1);
		}
		char ipv4_addr[16];	//IP地址共有16位包括\0
		if(!inet_ntop(AF_INET,(void *)&cin.sin_addr,ipv4_addr,sizeof(cin)))
		{
			perror("inet_ntop");
			exit(1);
		}
		printf("Client:(%s,%d)is connect!\n",ipv4_addr,ntohs(cin.sin_port));

		pthread_create(&tid,NULL,client_data_handle,(void *)&newfd);	//创建线程
	}

	close(fd);

	return 0;
}

void* client_data_handle(void* arg)
{
	int newfd = *(int *)arg;
	char buf[BUFSIZE];
	int ret = -1;
	printf("handle thread :newfd = %d\n",newfd);
	while(1)
	{
		do
		{
			bzero(buf,BUFSIZE);
			ret = read(newfd,buf,BUFSIZE-1);
		}while(ret < 1);
		if(ret < 0)
		{
			exit(1);
		}
		if(!ret)
		{
			break;
		}

		printf("receive data:%s\n",buf);

		if(!strncasecmp(buf,QUIT_STR,strlen(QUIT_STR)))
		{
			printf("client is exiting!\n");
			break;
		}
		
	}	
	close(newfd);
	return NULL;
}
