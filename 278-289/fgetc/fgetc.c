#include <stdio.h>

int main(int argc, char *argv[])
{
	FILE *fp;
	char writBuff[] = "hello world";
	char readBuff[128] = {0};
	
	fp = fopen("a.c","w+");
	if(fp == NULL)
	{
		printf("open file failed\n");
		return -1;
	}	

	fputs(writBuff,fp);

	fseek(fp,0,SEEK_SET);

	fgets(readBuff,128,fp);
	printf("readBuff is %s\n",readBuff);

	fclose(fp);

	return 0;
}
