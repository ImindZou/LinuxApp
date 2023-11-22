#include <stdio.h>
#include <string.h>

int main(void)
{
	char readBuff[128] = {0};
	int len = 0;

	//gets(readBuff);
	fgets(readBuff,128,stdin);

	len = strlen(readBuff);
	printf("len is %d\n",len);
	//fputs(readBuff,stdout);
	puts(readBuff);

	return 0;
}
