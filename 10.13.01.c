/**
 * @file 10.13.01.c
 * @brief getsid(),setsid()
 * @author LiWenGang
 * @date 2016-10-13
 */
#include<sys/types.h>
#include<wait.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

extern pid_t getsid(pid_t pid);

int main(int argc, char* argv[]){
	pid_t pid;
	pid=fork();
	switch(pid){
		case -1:perror("fork error");
				break;
		case  0:printf("setsid() | %d\n",setsid());
				printf("getsid() | %d\n",getsid(getpid()));
				printf("getpid() | %d\n",getpid());
				printf("-getppid()| %d\n",getppid());
				printf("-getpgrp()| %d\n",getpgrp());
				printf("getpid() | %d\n",getpid());
				_exit(EXIT_SUCCESS);
		default:sleep(3);
				printf("-getpid() | %d\n",getpid());
				printf("getppid()| %d\n",getppid());
				printf("-getpgrp()| %d\n",getpgrp());
				printf("getsid() | %d\n",getsid(0));
				exit(EXIT_SUCCESS);
				break;
	}
	return 0;
}

/*
 * 当parent进程创建了child进程时，进程组ID与parent进程的ID相等；会话的ID为parent进程的父进程的ID（这里的父进程的ID实际是指shell进程）
 * 当child进程使用setsid()设置了会话ID时，child进程的ID便会同时变为新的进程组ID，会话ID
 */
