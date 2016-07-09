#include<pthread.h>
#include<unistd.h>
#include<stdbool.h>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>

static pthread_mutex_t mtx=PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond=PTHREAD_COND_INITIALIZER;
static int avail=0;

static void* threadFunc(void* arg);

int main(int argc, char* argv[]){
	pthread_t tid;
	int flag;

	int totRequired=0;
	for(int i=1;i<argc;i++){
		totRequired+=atoi(argv[i]);
		flag=pthread_create(&tid,NULL,threadFunc,argv[i]);
		if(flag!=0){
			perror("error pthread_creat");
		}
	}

	int numConsumed=0;
	bool done=false;
	time_t t=time(NULL);

	for(;;){
		flag=pthread_mutex_lock(&mtx);
		if(flag!=0){
			perror("error pthread_mutex_lock");
		}
		while(avail==0){
			flag=pthread_cond_wait(&cond,&mtx);
			if(flag!=0){
				perror("error pthread_cond_wait");
			}
		}

		while(avail>0){
			numConsumed++;
			avail--;
			printf("T=%ld: numConsumed=%d\n",(long)(time(NULL)-t), numConsumed);
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

		flag=pthread_cond_signal(&cond);
		if(flag!=0){
			perror("pthread_cond_signal");
		}
	}

	return NULL;
}
