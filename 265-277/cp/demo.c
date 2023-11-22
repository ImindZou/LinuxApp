#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/*
   int close(int fd);
   int open(const char *pathname, int flags);
   int open(const char *pathname, int flags, mode_t mode);
   ssize_t write(int fd, const void *buf, size_t count);
   ssize_t read(int fd, void *buf, size_t count);

*/

int main(int argc,char *argv[])
{
	int src_fd;
	int des_fd;
	char readBuff[1024] = {0};
	int nRet = 0;

	if(argc != 3)
	{
		printf("error:arguments is less\n");
		return -1;
	}

	src_fd = open(argv[1],O_RDWR);

	nRet = read(src_fd,&readBuff[0],1024);

	des_fd = open(argv[2],O_RDWR|O_CREAT,0755);

	write(des_fd,readBuff,nRet);

	close(src_fd);
	close(des_fd);

	return 0;
}

/*执行流程
 *
 * 打开源文件
 * 读取src文件到缓存数组
 * 打开目标文件
 * 写入目标文件
 * 关闭目标文件和源文件
 * ./a.out src.c  des.c
 *
 * */
