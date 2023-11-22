#include <stdio.h>

int main(void)
{
	FILE *fp;
	int i = 10;

	fp = fopen("a.c","w+");
	if(fp == NULL)
	{
		printf("open file failed\n");
		return -1;
	}
	fprintf(fp,"open file success %d",i);
	while(1);
	fclose(fp);


	return 0;
}
