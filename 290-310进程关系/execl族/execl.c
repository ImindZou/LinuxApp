#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

//pid_t fork(void);
//int execl(const char *pathname, const char *arg, ...
//                       /* (char  *) NULL */);

int i = 200;
int main(int argc, char *argv[])
{
	pid_t pid;
	
	pid = fork();
	printf("Nomal i = %d\n",i);

	//father process
	if(pid > 0)
	{
		i += 400;
		printf("This is father process%d\n",getpid());
		printf("father i = %d\n",i);
	}	
	else if(pid == 0)
	{
		//execl("/home/z/LinuxAPP/290-310进程关系/execl族/hello","./hello",NULL);
		//execl("/bin/ls","ls","-l",NULL);
		execlp("ps","ps","aux",NULL);
		perror("execvp");
		i-= 200;
		printf("This is child process %d,ppid is %d\n",getpid(),getppid());
		printf("child i = %d\n",i);
	}
	for(int i=0; i<3; i++)
	{
		printf("-----i=%d\n",i);
	}

	return 0;
}

