/**
 * @file 10.14.01.c
 * @brief daemon|守护进程
 * @author LiWenGang
 * @date 2016-10-14
 */
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<unistd.h>
#include<assert.h>
#include<fcntl.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>

extern int getdtablesize(void);

int main(int argc, char* argv[]){
	char* buf="Hello world, This is a daemon program\n";
	pid_t pid=fork();

	switch(pid){
		case -1:perror("fork error");
				break;
		case  0:break;
		default:exit(EXIT_SUCCESS);
				break;
	}
	setsid();
	chdir("/home/li/Workspace/Temp");
	umask(0);
	for(int i=0;i<getdtablesize();i++){
		close(i);
	}
	
	int fd;
	ssize_t size;

	while(1){
		fd=open("test.log",O_RDWR|O_CREAT|O_APPEND,S_IRUSR|S_IWUSR);
		assert(fd!=-1);

		size=write(fd,buf,strlen(buf));
		assert(size!=-1);
		close(fd);

		sleep(5);
		printf("Never output!\n");
	}

	return 0;
}
