/**
 * @file 7.11.01.c
 * @brief setsid(),getsid()
 * @author LiWenGang
 * @date 2016-07-11
 */
#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>

pid_t getsid(pid_t pid);

int main(int argc, char* argv[]){
	if(fork()!=0){
		_exit(EXIT_SUCCESS);
	}
	if(setsid()==-1){
		printf("setsid\n");
	}
	printf("PID=%d|PGID=%d|SID=%d\n",getpid(),getpgrp(),getsid(0));
	if(open("/dev/tty",O_RDWR)==-1){
		perror("open /dev/tty");
	}
	return 0;
}

