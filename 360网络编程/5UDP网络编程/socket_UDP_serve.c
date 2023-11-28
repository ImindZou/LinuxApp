#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>          /* See NOTES */
#include <stdlib.h>
#include <arpa/inet.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>


#define SERV_PORT 5001
#define SERV_IP_ADDR "192.168.80.131"
#define BUFSIZE 1024
#define QUIT_STR "QUIT"

int main(void)
{
	//1.socket
	int fd = -1;
	struct sockaddr_in sin;
	fd = socket(AF_INET,SOCK_DGRAM,0);	//针对UDP的DGRAM
	if(fd < 0)
	{
		perror("socket");
		exit(1);
	}
	int b_reuser = 1;
	//2.addr重映射
	setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,&b_reuser,sizeof(int));

	//3.bind绑定
	bzero(&sin,sizeof(sin));
	
	sin.sin_family = AF_INET;//ipv4
	sin.sin_port = htons(SERV_PORT);
	sin.sin_addr.s_addr = htons(INADDR_ANY);

	if(bind(fd,(struct sockaddr*)&sin,sizeof(sin)) < 0)
	{
		perror("bind");
		exit(1);
	}

	//接受请求
	char buf[BUFSIZE];
	struct sockaddr_in cin;
	socklen_t addrlen = sizeof(cin);
	while(1)
	{
		bzero(buf,BUFSIZE);
		if(recvfrom(fd,buf,BUFSIZE-1,0,(struct sockaddr*)&cin,&addrlen) < 0)	
		{
			perror("recvfrom");
			continue;
		}

		char ipv4_addr[16];
		if(!inet_ntop(AF_INET,(void *)&cin.sin_addr,ipv4_addr,sizeof(cin)))
		{
			perror("inet_ntop");
			exit(1);
		}
		printf("receive from(%s,%d),data:%s\n",ipv4_addr,ntohs(cin.sin_port),buf);
		if(!strncasecmp(buf,QUIT_STR,strlen(QUIT_STR)))
		{
			printf("client(%s:%d) is exiting!\n",ipv4_addr,ntohs(cin.sin_port));
		}
	}
	close(fd);

	return 0;
}
