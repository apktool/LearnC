/**
 * @file 7.04.05.c
 * @brief 孤儿进程
 * @author LiWenGang
 * @date 2016-07-04
 */
#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int main(int argc,char* argv[]){
	pid_t pid;
	pid=fork();
	switch(pid){
		case -1:perror("error fork\n");
				exit(EXIT_FAILURE);
				break;
		case  0:printf("I am child\n");
				sleep(3);
				printf("pid=%d\tppid=%d\n",getpid(),getppid());
				exit(EXIT_SUCCESS);
				break;
		default:printf("I am parent\n");
				sleep(1);
				exit(EXIT_SUCCESS);
				break;
	}
}

/*
 * 孤儿进程：
 * 父进程退出，而它的一个子进程或多个子进程还在运行，那么那些子进程将会成为孤儿进程。
 * 孤儿进程将被init进程（pid=1）所收养，并由init进程对它们完成状态收集工作。
 */
