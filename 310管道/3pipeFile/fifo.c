#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

//int mkfifo(const char *pathname, mode_t mode);
int main(void)
{
	char *str = "hello world";
	int fd;
	fd = open("./myfifo",O_WRONLY);
	if(fd < 0)
	{
		return -1;
	}
	printf("open fifo success!\n");

	write(fd,str,strlen(str));

	close(fd);
	return 0;
}

