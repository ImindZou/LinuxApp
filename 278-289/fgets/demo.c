#include <stdio.h>

int main(int argc, char *argv[])
{
	FILE *fp;
	char writeBuff[] = "hello world";
	fp = fopen("a.c","w+");
	if(fp == NULL)
	{
		printf("open failed!\n");
		return -1;
	}

	fputs(writeBuff,fp);
	while(1);
	
	fclose(fp);
	return 0;
}
