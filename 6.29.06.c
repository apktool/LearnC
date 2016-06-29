/**
 * @file 6.29.06.c
 * @brief signal(),sleep()
 * @author LiWenGang
 * @date 2016-06-29
 */
#include<signal.h>
#include<unistd.h>
#include<stdio.h>

static void sigHandler(int sig){
	printf("Ouch, Damn!\n");
}

int main(int argc, char* argv[]){
	if(signal(SIGINT,sigHandler)==SIG_ERR){
		printf("signal\n");
	}
	
	for(int i=0;;i++){
		printf("count: %d\n",i);
		sleep(2);
	}
	return 0;
}
