/**
 * @file 7.08.01.c
 * @brief pthread_mutexattr_init(),pthread_mutexattr_settype(),pthread_mutex_init(),pthread_mutexattr_destroy()
 * @author LiWenGang
 * @date 2016-07-08
 */
#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>

int pthread_mutexattr_settype(pthread_mutexattr_t *attr, int type);
static void* pthreadFunc(void*);
static int cnt=0;

int main(int argc, char* argv[]){
	pthread_t thd1,thd2;
	int loops=100000;
	int flag;

	flag=pthread_create(&thd1,NULL,pthreadFunc,&loops);
	if(flag!=0){
		perror("error pthread_create");
	}

	flag=pthread_create(&thd2,NULL,pthreadFunc,&loops);
	if(flag!=0){
		perror("error pthread_create");
	}

	flag=pthread_join(thd1,NULL);
	if(flag!=0){
		perror("error pthread_join");
	}

	flag=pthread_join(thd2,NULL);
	if(flag!=0){
		perror("error pthread_join");
	}

	printf("cnt=%d\n",cnt);
	return 0;
}

static void* pthreadFunc(void *s){
	int loops=*((int*)s);
	int flag;
	pthread_mutex_t mtx;
	pthread_mutexattr_t mtxAttr;

	flag=pthread_mutexattr_init(&mtxAttr);
	if(flag!=0){
		perror("error pthread_mutexattr_init");
	}
	flag=pthread_mutexattr_settype(&mtxAttr,PTHREAD_MUTEX_ERRORCHECK_NP);
	if(flag!=0){
		perror("error pthread_mutexattr_settype");
	}
	flag=pthread_mutex_init(&mtx,&mtxAttr);
	if(flag!=0){
		perror("error pthread_mutex_init");
	}
	for(int i=0;i<loops;i++){
		cnt++;
	}
	flag=pthread_mutexattr_destroy(&mtxAttr);
	if(flag!=0){
		perror("error pthread_mutexattr_destory");
	}
	return NULL;
}

/*
 * 动态分配互斥量
 */ 
