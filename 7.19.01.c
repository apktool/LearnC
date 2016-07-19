/**
 * @file 7.19.01.c
 * @brief daemon|守护进程|SIGHUP
 * @author LiWenGang
 * @date 2016-07-19
 */
#include<sys/types.h>
#include<sys/stat.h>
#include<signal.h>
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

static volatile sig_atomic_t hupReceived=0;
static void sighupHandler(int sig);

int main(int argc, char* argv[]){
	const int SLEEP_TIME=15;
	int count=0;
	int unslep;

	struct sigaction sa;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags=SA_RESTART;
	sa.sa_handler=sighupHandler;
	if(sigaction(SIGHUP,&sa,NULL)==-1){
		perror("error sigation");
	}
	if(becomeDaemon(0)==-1){
		perror("error becomeDaemon");
	}


	sleep(20);
	return 0;
}

static void sighupHandler(int sig){
	hupReceived=1;
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
	if(!(flags & BD_NO_UMASK)){
		umask(0);
	}
	if(!(flags & BD_NO_CHDIR)){
		chdir("/");
	}

	int maxfd,fd;

	if(!(flags & BD_NO_CLOSE_FILES)){
		maxfd=sysconf(_SC_OPEN_MAX);
		if(maxfd==-1){
			maxfd=BD_MAX_CLOSE;
		}
		for(fd=0;fd<maxfd;fd++){
			close(fd);
		}
	}
	if(!(flags & BD_NO_REOPEN_STD_FDS)){
		close(STDIN_FILENO);
		if(fd!=STDIN_FILENO){
			return -1;
		}
		if(dup2(STDIN_FILENO,STDOUT_FILENO)!=STDOUT_FILENO){
			return -1;
		}
		if(dup2(STDIN_FILENO,STDERR_FILENO)!=STDERR_FILENO){
			return -1;
		}
	}
	return 0;
}
