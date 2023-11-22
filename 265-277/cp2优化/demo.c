#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

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
	char readBuff[128] = {0};
	int nRet = 0;

	if(argc != 3)
	{
		printf("error:arguments is less\n");
		return -1;
	}

	src_fd = open(argv[1],O_RDWR);
	if(src_fd < 0)
	{
		printf("open source file %d  failed\n",src_fd);
		return -2;
	}
	des_fd = open(argv[2],O_RDWR|O_CREAT,0755);
	if(des_fd < 0)
	{
		printf("open desting file %d failed\n",des_fd);
		return -3;
	}

	while(1)
	{
		nRet = read(src_fd,&readBuff[0],128);
		if(nRet < 128)
			break;
		write(des_fd,readBuff,nRet);
		memset(readBuff,0,128);
		
	}
	write(des_fd,readBuff,nRet);

	close(src_fd);
	close(des_fd);

	return 0;
}

/*执行流程
 *
 * 打开源文件
 * 打开目标文件
 * 循环读取源文件数据到目标文件数据，一次用128的数据，避免造成内存浪费
 * 加上判断nRet<128推出循环，并在循环之外把剩余的数据读取出来。
 * 关闭目标文件和源文件
 * ./a.out src.c  des.c
 *
 * */
/*
z@z:~/LinuxAPP/265-275/cp2优化$ gcc demo.c
z@z:~/LinuxAPP/265-275/cp2优化$ ./a.out
error:arguments is less
z@z:~/LinuxAPP/265-275/cp2优化$ ./a.out  test.txt test1.txt
z@z:~/LinuxAPP/265-275/cp2优化$ ls
a.out  demo.c  test1.txt  test.txt
*/
