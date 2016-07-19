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
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <stdarg.h>

#ifndef BECOME_DAEMON_H
#define BECOME_DAEMON_H
#define BD_NO_CHDIR 01
#define BD_NO_CLOSE_FILES 02
#define BD_NO_REOPEN_STD_FDS 04
#define BD_NO_UMASK 010
#define BD_MAX_CLOSE 8192
int becomeDaemon(int flags);
#endif

static void sighupHandler(int sig);
static void readConfigFile(const char* configFilename);
static void logOpen(const char* logFilename);
static void logClose(void);
static void logMessage(const char* format, ...);

static const char *LOG_FILE="/tmp/ds.log";
static const char *CONFIG_FILE="/tmp/ds.conf";

static volatile sig_atomic_t hupReceived=0;
static FILE *logfp;

int main(int argc, char* argv[]){
	const int SLEEP_TIME=15;
	int count=0;
	int unslept;

	struct sigaction sa;
	sigemptyset(&sa.sa_mask);
	//sa.sa_flags=SA_RESTART;
	sa.sa_flags=SA_NOCLDSTOP;
	sa.sa_handler=sighupHandler;
	if(sigaction(SIGHUP,&sa,NULL)==-1){
		perror("error sigation");
	}
	if(becomeDaemon(0)==-1){
		perror("error becomeDaemon");
	}

	logOpen(LOG_FILE);
	readConfigFile(CONFIG_FILE);

	unslept=SLEEP_TIME;

	for(;;){
		unslept=sleep(unslept);
		if(hupReceived){
			hupReceived=0;
			logClose();
			logOpen(LOG_FILE);
			readConfigFile(CONFIG_FILE);
		}
		if(unslept==0){
			count++;
			logMessage("Main: %d", count);
			unslept=SLEEP_TIME;	
		}
	}
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

static void logOpen(const char* logFilename){
	mode_t m;
	m=umask(077);
	logfp=fopen(logFilename,"a");
	umask(m);
	if(logfp==NULL){
		exit(EXIT_FAILURE);
	}
	setbuf(logfp,NULL);
	logMessage("Opened log file");
}

static void logClose(){
	logMessage("Closing log file");
	fclose(logfp);
}

static void readConfigFile(const char* configFilename){
	FILE* configfp;
#define SBUF_SIZE 100
	char str[SBUF_SIZE];

	configfp=fopen(configFilename,"r");
	if(configfp!=NULL){
		if(fgets(str,SBUF_SIZE,configfp)==NULL){
			str[0]='\0';
		}else{
			str[strlen(str)-1]='\0';
		}
		logMessage("Read config file:%s",str);
	}
	fclose(configfp);
}

static void logMessage(const char* format,...){
	va_list argList;
	const char *TIMESTAMP_FMT="%F %X";
#define TS_BUF_SIZE sizeof("YYYY-MM-DD HH:MM:SS")
	char timestamp[TS_BUF_SIZE];
	time_t t;
	struct tm *loc;

	t=time(NULL);
	loc=localtime(&t);
	if(loc==NULL||strftime(timestamp,TS_BUF_SIZE,TIMESTAMP_FMT,loc)==0){
		fprintf(logfp,"???Unknown time???:");
	}else{
		fprintf(logfp,"%s:",timestamp);
	}

	va_start(argList,format);
	vfprintf(logfp,format,argList);
	fprintf(logfp,"\n");
	va_end(argList);
}
