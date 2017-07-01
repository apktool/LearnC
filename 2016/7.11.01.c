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

/*
 * ps -p $$ -o 'pid pgid sid command'
 * 使用setsid()来创建一个新会话，为了检查该进程已经不再拥有控制终端了，这个程序尝试打开一个特殊文件/dev/tty。
 * 如果调用进程不是进程组的首进程，那么setsid()会创建一个新会话；
 * 如果调用进程是一个进程组的手进程，那么setsid()会报出EPERM错误。
 */ 
