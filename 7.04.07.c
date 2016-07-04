/**
 * @file 7.04.07.c
 * @brief 僵尸进程|通过信号量机制解决
 * @author LiWenGang
 * @date 2016-07-04
 */
#include<sys/types.h>
#include<sys/wait.h>
#include<signal.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

static void sig_child(int signo);

int main(int argc, char* argv[]){

	signal(SIGCHLD,sig_child);

	pid_t pid;
	pid=fork();
	switch(pid){
		case -1:perror("error fork\n");
				exit(EXIT_FAILURE);
				break;
		case  0:printf("I am child. pid=%d\n",getpid());
				_exit(EXIT_SUCCESS);
				break;
		default:printf("I am father. pid=%d\n",getpid());
				sleep(2);
				system("ps -o pid,ppid,state,tty,command");
				printf("father proccess is exiting\n");
				exit(EXIT_SUCCESS);
				break;
	}
	return 0;
}

static void sig_child(int signo){
	pid_t pid;
	int stat;

	while((pid=waitpid(-1,&stat,WNOHANG))>0){
		printf("child %d terminated\n",pid);
	}
}
