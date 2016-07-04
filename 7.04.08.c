/**
 * @file 7.04.08.c
 * @brief 僵尸进程|通过fork()两次解决
 * @author LiWenGang
 * @date 2016-07-04
 */
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char* argv[]){
	pid_t pid;
	pid=fork();
	switch(pid){
		case -1:perror("error fork\n");
				break;
		case  0:printf("I am the first child.|pid=%d|ppid=%d\n",getpid(),getppid());
				pid=fork();
				switch(pid){
					case -1:perror("error fork\n");
							exit(EXIT_FAILURE);
							break;
					case  0:sleep(3);
							printf("I am the second child.|pid=%d|ppid=%d\n",getpid(),getppid());
							_exit(EXIT_SUCCESS);
					default:printf("first process is end\n");
							exit(EXIT_SUCCESS);
				}
				_exit(EXIT_SUCCESS);
		default:if(pid!=waitpid(pid,NULL,0)){
					perror("waitpid error\n");
				}
				exit(EXIT_SUCCESS);
	}
	return 0;
}


/* 原理：
 * 让子进程称为孤儿进程，从而使其父进程称为init进程，通过init处理僵尸进程
 */

