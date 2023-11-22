#include <stdio.h>
#include <string.h>

//size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
//size_t fwrite(const void *ptr, size_t size, size_t nmemb,FILE *stream);
//int fseek(FILE *stream, long offset, int whence);


int main(void)
{	
	FILE *fp = NULL;
	int nRet = 0;
	char readBuff[12] = {0};
	memset(readBuff,0,12);
	char *writeBuff = "hello world";

	fp = fopen("mm","r+");
	if(fp == NULL)
	{
		printf("open failed!\n");
		return -1;
	}
	printf("open success!\n");

	nRet = fread(readBuff,4,2,fp);
	if(nRet <= 0)
	{
		printf("fread failed\n");
		return -3;
	}

	printf("fread %s\n",readBuff);

	nRet = fseek(fp,0,SEEK_SET);
	if(nRet)
	{
		printf("fseek failed\n");
		return -5;
	}


	nRet = fwrite(writeBuff,4,2,fp);
	if(nRet <= 0)
	{
		printf("fwrite failed\n");
		return -4;
	}
	printf("fwrite success!\n");

	nRet = fclose(fp);
	if(nRet)
	{
		printf("fclose failed!\n");
		return -2;
	}
	printf("close success!\n");
	
	return 0;
}


