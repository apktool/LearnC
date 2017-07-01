/**
 * @file 10.12.02.c
 * @brief getpid(),getppid(),getpgid(),getpgrp()
 * @author LiWenGang
 * @date 2016-10-12
 */
#include<sys/types.h>
#include<wait.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

extern pid_t getpgid(pid_t pid);

int main(int argc, char* argv[]){
	pid_t pid;
	pid=fork();
	switch(pid){
		case -1:perror("error fork");
				break;
		case  0:printf("getpid()  | %d\n",getpid());
				printf("getppid() | %d\n",getppid());
				printf("getpgid() | %d\n",getpgid(0));
				printf("getpgid() | %d\n",getpgid(getpid()));
				printf("getpgrp() | %d\n",getpgrp());
				_exit(EXIT_SUCCESS);
		default:sleep(3);
				printf("-getpid()  | %d\n",getpid());
				printf("-getppid() | %d\n",getppid());
				printf("-getpgid() | %d\n",getpgid(0));
				printf("-getpgid() | %d\n",getpgid(getpid()));
				printf("-getpgrp() | %d\n",getpgrp());
				wait(NULL);
				exit(EXIT_SUCCESS);
	}

	return 0;
}
