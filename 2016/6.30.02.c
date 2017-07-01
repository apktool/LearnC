/**
 * @file 6.30.02.c
 * @brief mkstemp(),fork(),fcntl()
 * @author LiWenGang
 * @date 2016-07-02
 */
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>

int mkstemp(char*);

int main(int argc,char* argv[]){
	int fd,flags;
	char temp[]="tempXXXXXX";

	setbuf(stdout,NULL);

	printf("---%s---%s---%d---\n",__FILE__,__FUNCTION__,__LINE__);

	fd=mkstemp(temp);
	if(fd==-1){
		printf("mkstemp error\n");
	}
	printf("File offset before fork():%ld\n",lseek(fd,0,SEEK_CUR));

	flags=fcntl(fd,F_GETFL);
	if(flags==-1){
		printf("fcnt error\n");
	}

	printf("O_APPEND flag before fork() is:%s\n",(flags&O_APPEND)?"on":"off");
	pid_t childPID;
	childPID=fork();
	switch(childPID){
		case -1:printf("fork error\n");break;
		case 0: if(lseek(fd,5,SEEK_SET)==-1){
				   printf("lseek error");
				}
				flags=fcntl(fd,F_GETFL);
				if(flags==-1){
					printf("fcntl-F_GETFL");
				}
				flags|=O_APPEND;
				if(fcntl(fd,F_SETFL,flags)==-1){
					printf("fcntl-F_SETFL");
				}
				_exit(0);
				break;
		default:
				if(wait(NULL)==-1){
					printf("wait");
				}
				printf("Child has exited\n");
				printf("File offset in parent:%lld\n",(long long)lseek(fd,0,SEEK_CUR));
				flags=fcntl(fd,F_GETFL);
				if(flags==-1){
					printf("fcntl-F_GETFL");
				}
				printf("O_APPEND flag in parent is:%s\n",(flags&O_APPEND)?"on":"off");
				break;
	}
	return 0;
}
