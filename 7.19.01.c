/**
 * @file 7.19.01.c
 * @brief daemon|守护进程|SIGHUP
 * @author LiWenGang
 * @date 2016-07-19
 */
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

#ifndef BECOME_DAEMON_H
#define BECOME_DAEMON_H
#define BD_NO_CHDIR 01
#define BD_NO_CLOSE_FILES 02
#define BD_NO_REOPEN_STD_FDS 04
#define BD_NO_UMASK 010
#define BD_MAX_CLOSE 8192
int becomeDaemon(int flags);
#endif

int main(int argc, char* argv[]){
	int flag=becomeDaemon(0);
	if(flag!=0){
		perror("error becomeDaemon");
	}else{
		printf("becomeDaemon\n");
	}
	sleep(20);
	return 0;
}

int becomeDaemon(int flags){
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
	return 0;
}
