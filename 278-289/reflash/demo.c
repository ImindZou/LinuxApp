#include <stdio.h>

int main(int argc, char *argv[])
{
	//printf("hello world");
	//fputs("hello world",stdout);
	fputs("hello world",stderr);	//err是无缓存
	//fflush(stdout);	//强制把用户态写到内核态
	while(1);
	
	return 0;
}
