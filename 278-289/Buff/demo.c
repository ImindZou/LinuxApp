#include<stdio.h>
#include <unistd.h>

//ssize_t write(int fd, const void *buf, size_t count);

int main(void)
{
	char readBuff[20] = "hello world!";
	printf("%s",readBuff);
	//write(1,readBuff,sizeof(readBuff));
	while(1);

	return 0;
}

/*缓存的概念
 *
 * 我们程序中的缓存，就是你想从内核中读取的（数组）————用户空间的缓存
 *
 * 每打开一个文件，内核在内核空间中也会开辟一块缓存，这个叫内核空间缓存
 * 文件IO的写即是将用户空间中的缓存写道内核空间的缓存中
 * 文件IO的读取即是将内核空间的缓存写道用户空间的缓存
 *
 * 标准IO的库函数中也有一个缓存，这个缓存成为————库缓存
 *
 *
 * 库缓存的特点：
 *
 * 遇到\n时，会将库缓存的内热哦你写道内核缓存中，即调用了系统调用函数
 *
 * 库缓存写满时，会调用系统调用函数，将库缓存的内容写在内核缓存中。1024为满。
 *
 * */
