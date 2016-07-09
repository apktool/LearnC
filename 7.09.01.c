#include<pthread.h>
#include<unistd.h>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

static pthread_mutex_t mtx=PTHREAD_MUTEX_INITIALIZER;
static int avail=0;

static void* threadFunc(void* arg);

int main(int argc, char* argv[]){
	int totRequired=0;

	int flag;

	time_t t;
	t=time(NULL);

	pthread_t tid;

	for(int i=1;i<argc;i++){
		totRequired+=atoi(argv[i]);
		flag=pthread_create(&tid,NULL,threadFunc,argv[i]);
		if(flag!=0){
			perror("error pthread_create");
		}
	}

	int numConsumed=0;
	bool done=false;

	for(;;){
		flag=pthread_mutex_lock(&mtx);
		if(flag!=0){
			perror("error pthread_mutex_lock");
		}
		while(avail>0){
			numConsumed++;
			avail--;
			printf("T=%ld:numConsumed=%d\n",(long)(time(NULL)-t),numConsumed);
			done=numConsumed>=totRequired;
		}
		flag=pthread_mutex_unlock(&mtx);
		if(flag!=0){
			perror("error pthread_mutex_unlock");
		}
		if(done){
			break;
		}
	}
	return 0;
}

static void* threadFunc(void* arg){
	int cnt=atoi((char*)arg);
	int flag;

	for(int i=0;i<cnt;i++){
		sleep(1);

		flag=pthread_mutex_lock(&mtx);
		if(flag!=0){
			perror("error pthread_mutex_lock");
		}
		avail++;

		flag=pthread_mutex_unlock(&mtx);
		if(flag!=0){
			perror("error pthread_mutex_unlock");
		}
	}

	return NULL;
}
