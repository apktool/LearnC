/**
 * @file 7.12.01.c
 * @brief 在sheel中处理SIGHUP信号
 * @author LiWenGang
 * @date 2016-07-12
 */
#include<sys/types.h>
#include<unistd.h>
#include<signal.h>
#include<stdio.h>

static void handler(int);

int main(int argc, char* argv[]){
	struct sigaction sa;

	setbuf(stdout,NULL);

	sigemptyset(&sa.sa_mask);
	sa.sa_flags=0;
	sa.sa_handler=handler;
	if(sigaction(SIGHUP,&sa,NULL)==-1){
		perror("sigaction");
	}

	pid_t childPid;
	childPid=fork();
	if(childPid==-1){
		perror("fork");
	}
	if(childPid==0&&argc>1){
		if(setpgid(0,0)==-1){
			perror("setpgid");
		}
	}
	printf("PID=%d|PPID=%d|PGID=%d|SID=%d\n",getpid(),getppid(),getpgrp(),getsid(0));

	alarm(3);

	for(;;){
		pause();
		printf("%d: caught SIGHUP\n",getpid());
	}
	return 0;

}

static void handler(int sig){

}

/*
 * 本程序演示了shell接收SIGHUP信号并向创建的任务发送SIGHUP信号的过程。
 * 创建一个子进程，然后让父进程和子进程暂停执行以捕获SIGHUP信号，并在接收到该信号时打印一条消息。
 * 如果在执行程序时使用了一个可选的命令行参数（任意字符串），那么子进程会将其自身放置在一个不同的进程组中（在同一个会话中）
 * 这个功能说明了shell不会向不是它创建的进程组发送SIGHUP信号，即该进程组与shell位于同一个会话中
 * gcc 7.12.01.c -o a.out -Wall -std=c11 -D_XOPEN_SOURCE=700
 */
