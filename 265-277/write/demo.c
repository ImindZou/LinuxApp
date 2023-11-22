#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

//int open(const char *pathname, int flags);
//int open(const char *pathname, int flags, mode_t mode);
//ssize_t write(int fd, const void *buf, size_t count);

int main(void)
{
	int fd;
	char writeBuff[128] = {0};
	char *test = "hello world";
	strcpy(writeBuff,test);

	fd = open("mm",O_RDWR|O_CREAT,0755);
	if(fd == -1)
	{
		printf("open file failed \n");
		perror("why");
		return -1;
	}
	printf("open file success \n");

	write(fd,&writeBuff[0],11);
	close(fd);

	return 0;
}



