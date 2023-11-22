#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define filename "mm"
#define writeNum 128
#define readNum 12

//int open(const char *pathname, int flags);
//int open(const char *pathname, int flags, mode_t mode);
//ssize_t write(int fd, const void *buf, size_t count);
//ssize_t read(int fd, void *buf, size_t count);
//off_t lseek(int fd, off_t offset, int whence);


int main(void)
{
	int fd;
	int offset;
	//char writeBuff[writeNum] = {0};
	char readBuff[readNum] = {0};		//read的时候没读到/0,改成12就可以读到
	/*char *test = "hello world";
	if(writeNum < (strlen(test)+1))
	{
		printf("error:writeBuff less than test\n");
		return -1;
	}
	strcpy(writeBuff,test);
	*/

	fd = open(filename,O_RDWR|O_CREAT,0755);
	if(fd == -1)
	{
		printf("open file failed \n");
		perror("why");
		return -1;
	}
	printf("open file success \n");

	offset = lseek(fd,1,SEEK_CUR);
	printf("offset is %d\n",offset);
//	write(fd,&writeBuff[0],11);
	read(fd,&readBuff,1);
	printf("%s\n",readBuff);
	close(fd);

	return 0;
}



