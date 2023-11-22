#include <stdio.h>

int main(int argc,char *argv[])
{
	printf("param total %d\n",argc);
	printf("param first is %s\n",argv[0]);
	printf("param second is %s\n",argv[1]);
	printf("param third is %s\n",argv[2]);

	return 0;
}
/*
z@z:~/LinuxAPP/265-275/main$ ./a.out
param total 1
param first is ./a.out
param second is (null)
param third is SHELL=/bin/bash
z@z:~/LinuxAPP/265-275/main$ ./a.out asd dsa
param total 3
param first is ./a.out
param second is asd
param third is dsa 
*/
