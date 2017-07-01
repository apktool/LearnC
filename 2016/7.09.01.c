/**
 * @file 7.09.01.c
 * @brief 消费者，生产者。不使用条件变量
 * @author LiWenGang
 * @date 2016-07-09
 */
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

/*
 * 关于多线程编程应该特别注意程序的执行方式，加锁的位置。
 * 比如在本程序中:
 * threadFunc函数中，avail每被加锁一次，本身自增一次，解锁后，接着会执行main函数中的加锁->自减->解锁;
 * 接着又会执行threadFunc函数中的加锁->自增->解锁；依次类推
 * 直至满足for循环，彻底退出threadFunc函数。
 */ 
