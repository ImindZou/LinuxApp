#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(void)
{
	int ret;
	int fd;
	char readBuff[50] = {0};
	int nread;
	ret = mkfifo("./myfifo",0755);
	if(fd < 0)
	{
		return -1;
	}
	printf("makefifo success!\n");

	fd = open("./myfifo",O_RDONLY);
	if(fd <0)
	{
		return -1;
	}
	printf("open fifo sucess\n");

	nread = read(fd,readBuff,50);
	printf("read %d byte from fifo %s:\n",nread,readBuff);

	close(fd);
	return 0;
}

