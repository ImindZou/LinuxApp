#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <errno.h>



#define SER_PORT  5001
#define SERV_IP_ADDR "192.168.80.131"
#define BUFSIZE 1024
#define QUIT_STR "QUIT"


int main(int argc,char **argv[])
{
	if(argc < 3)
	{
		exit(1);
	}
	int fd = -1;
	fd = socket(AF_INET,SOCK_DGRAM,0);
	if(fd < 0)
	{
		perror("socket");
		exit(1);
	}
	int port = -1;
	port = atoi(argv[2]);

	struct sockaddr_in sin;

	bzero(&sin,sizeof(sin));

	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = inet_addr(argv[1]);

	char buf[BUFSIZE];
	while(1)
	{
		bzero(buf,BUFSIZE);

		if(fgets(buf,BUFSIZE-1,stdin) == NULL)
		{
			perror("fgets");
			continue;
		}

		sendto(fd,buf,strlen(buf),0,(struct sockaddr*)&sin,sizeof(sin));

		if(!strncasecmp(buf,QUIT_STR,strlen(QUIT_STR)))
		{
			printf("client is exited!\n");
			break;
		}

	}
	//close(fd);

	return 0;
}

