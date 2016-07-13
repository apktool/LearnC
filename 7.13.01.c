#include<signal.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

static void handler(int);

int main(int argc, char* argv[]){
	struct sigaction sa;
	sa.sa_flags=SA_NOCLDSTOP;
	sa.sa_handler=handler;

	int flag=sigaction(SIGINT,&sa,NULL);
	if(flag==-1){
		perror("error sigaction");
	}

	printf("pid=%d|pgid=%d|ppid=%d\n",getpid(),getpgrp(),getppid());
	for(int i=0;;i++){
		printf("count:%d\n",i);
		sleep(2);
	}
	return 0;
}

/*
int main(int argc, char* argv[]){
	if(signal(SIGINT,handler)==SIG_ERR){
		printf("error signal\n");
	}

	printf("pid=%d|pgid=%d|ppid=%d\n",getpid(),getpgrp(),getppid());
	for(int i=0;;i++){
		sleep(2);
		printf("count:%d\n",i);
	}
}
*/
static void handler(int sig){
	printf("What's the fuck");
}
