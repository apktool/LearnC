/**
 * @file 7.18.01.c
 * @brief daemon|创建守护进程
 * @author LiWenGang
 * @date 2016-07-18
 */
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

#ifndef BECOME_DEMON_H
#define BECOME_DEMON_H

#define BD_NO_CHDIR 01
#define BD_NO_CLOSE_FILES 02
#define BD_NO_REOPEN_SID_FDS 04
#define BD_NO_UMASK 010
#define BD_MAX_CLOSE 8192

int becomeDaemon(int flags);
#endif

int main(int argc, char* argv[]){
	int flag=becomeDaemon(0);
	if(flag==-1){
		perror("error becomeDaemon");
	}else{
		printf("success becomeDaemon");
	}
	sleep(30);
	return 0;
}

int becomeDaemon(int flags){
	int maxfd, fd;

	switch(fork()){
		case -1:return -1;
		case  0:break;
		default:_exit(EXIT_SUCCESS);
	}

	if(setsid()==-1){
		return -1;
	}

	switch(fork()){
		case -1:return -1;
		case  0:break;
		default:_exit(EXIT_SUCCESS);
	}

	if(!(flags & BD_NO_UMASK)){
		umask(0);
	}
	if(!(flags & BD_NO_CHDIR)){
		chdir("/");
	}
	if(!(flags & BD_NO_CLOSE_FILES)){
		maxfd=sysconf(_SC_OPEN_MAX);
		if(maxfd==-1){
			maxfd=BD_MAX_CLOSE;
		}
		for(fd=0;fd<maxfd;fd++){
			close(fd);
		}
	}
	if(!(flags & BD_NO_REOPEN_SID_FDS)){
		close(STDIN_FILENO);
		fd=open("/dev/null",O_RDWR);
		if(fd!=STDIN_FILENO){
			return -1;
		}
		if(dup2(STDIN_FILENO, STDOUT_FILENO)!=STDOUT_FILENO){
			return -1;;
		}
		if(dup2(STDIN_FILENO,STDERR_FILENO)!=STDERR_FILENO){
			return -1;
		}
	}
	return 0;
}

/*
 * gcc 7.18.01.c -o temp -Wall -std=c11
 * ps -C temp -o "pid,ppid,pgid,tty,command"
 */ 

/*
 * SIGINT  | 中断字符 | Ctrl+C
 * SIGQUIT | 退出字符 | Ctrl+\
 * SIGSTP  | 挂起字符 | Ctrl+Z
 */ 
