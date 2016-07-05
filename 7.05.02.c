#include<sys/types.h>
#include<sys/wait.h>
#include<signal.h>
#include<unistd.h>
#include<fcntl.h>
#include<sched.h>
#include<errno.h>
#include<stdio.h>
#include<stdlib.h>

#ifndef CHILD_SIG
#define CHILD_SIG SIGUSR1
#endif

static int childFunc(void* arg){
	if(close(*((int*)arg))==-1){
		printf("close\n");
	}
	return 0;
}

int main(int argc, char* argv[]){
	const int stack_size=65536;
	char* stack;
	char* stackTop;
	int s,fd,flags;

	fd=open("/dev/null",O_RDWR);
	if(fd==-1){
		printf("open\n");
	}

	flags=(argc>1)?CLONE_FILES:0;

	stack=(char*)malloc(stack_size);
	if(stack==NULL){
		printf("malloc\n");
	}
	stackTop=stack+stack_size;

	if(CHILD_SIG!=0&&CHILD_SIG!=SIGCHLD){
		if(signal(CHILD_SIG,SIG_IGN)==SIG_ERR){
			printf("signal\n");
		}
	}

	if(clone(childFunc,stackTop,flags|CHILD_SIG,(void*)&fd)==-1){
		printf("clone\n");
	}

	if(waitpid(-1,NULL,(CHILD_SIG!=SIGCHLD)?_WCHONE:0)==-1){
		printf("waitpid\n");
	}
	printf("child has terminated\n");

	s=write(fd,"x",1);
	if(s==-1&&errno==EBADF){
		printf("file descriptor %d has been closed\n",fd);
	}else if(s==-1){
		printf("write() on file descriptor %d failed\n",fd);
	}else{
		printf("write() on file descriptor %d successed\n",fd);
	}
	return 0;
}
