/**
 * @file 7.04.02.c
 * @brief 等待状态值
 * @author LiWenGang
 * @date 2016-07-04
 */
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<errno.h>

void PrintWaitStatus(const char* msg, int status);
char *strsignal(int sig);

int main(int argc,char* argv[]){
	pid_t pid;
	pid=fork();
	switch(pid){
		case -1:printf("error fork");break;
		case  0:_exit(0);break;
	}
	PrintWaitStatus("hello world",pid);
	return 0;
}

void PrintWaitStatus(const char* msg, int status){
	if(msg!=NULL){
		printf("%s\n",msg);
	}
	if(WIFEXITED(status)){
		printf("Child exited, status=%d\n",WEXITSTATUS(status));
	}else if(WIFSIGNALED(status)){
		printf("Child kill by signal %d(%s)\n",WTERMSIG(status),strsignal(WTERMSIG(status)));
	#ifdef WCOREDUMP
		if(WCOREDUMP(status)){
			printf("core dumped\n");
		}
	#endif
	}else if(WIFSTOPPED(status)){
		printf("child stopped by signal %d(%s)\n",WSTOPSIG(status),strsignal(WSTOPSIG(status)));
	#ifdef WIFCONTINUED
	}else if(WIFCONTINUED(status)){
		printf("child continued\n");
	#endif
	}else{
		printf("what happened to this child?(status=%x)\n",(unsigned int)status);
	}
}
