#include <stdio.h>

int main(void)
{
	char buf[128] = {0};
	int i = 10;
	sprintf(buf,"i = %d\n",i);
	printf("buf is %s\n",buf);

	return 0;
}
