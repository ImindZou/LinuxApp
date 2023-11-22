#include <stdio.h>

int main(void)
{
	FILE *fp = NULL;
	int nRet = 0;
	fp = fopen("mm","w");
	if(fp == NULL)
	{
		printf("open failed \n");
		return -1;
	}
	printf("open success \n");
	nRet = fclose(fp);
	if(nRet)
	{
		printf("close failed\n");
		return -2;
	}
	printf("close sucess\n");

	return 0;
}
