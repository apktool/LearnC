/**
 * @file 7.07.02.c
 * @brief pthread_create(),pthread_join(),pthread_mutex_lock(),pthread_mutex_unlock()
 * @author LiWenGang
 * @date 2016-07-07
 */
#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>

static int glob=0;
static void* threadFun(void*);
static pthread_mutex_t mtx=PTHREAD_MUTEX_INITIALIZER;//静态分配互斥量

int main(int argc, char* argv[]){
	pthread_t thd1,thd2;
	int loops,flag;

	loops=1000000;
	flag=pthread_create(&thd1,NULL,threadFun,&loops);
	if(flag!=0){
		perror("pthread create error\n");
	}
	flag=pthread_create(&thd2,NULL,threadFun,&loops);
	if(flag!=0){
		perror("pthread create error\n");
	}
	flag=pthread_join(thd1,NULL);
	if(flag!=0){
		perror("pthread join error");
	}
	flag=pthread_join(thd2,NULL);
	if(flag!=0){
		perror("pthread join error");
	}
	printf("glob=%d\n",glob);
	return 0;
}

static void* threadFun(void* arg){
	int loops=*((int*)arg);
	int loc,flag;
	for(int j=0;j<loops;j++){
		flag=pthread_mutex_lock(&mtx);
		if(flag!=0){
			printf("%d|pthread_mutex_lock",flag);
		}
		loc=glob;
		loc++;
		glob=loc;
		flag=pthread_mutex_unlock(&mtx);
		if(flag!=0){
			printf("%d|pthread_mutex_unlock",flag);
		}
	}
	return NULL;
}

/*
 * 关于此处有个疑问，当main()中的函数次序写成如下形式的时候
 *	flag=pthread_create(&thd1,NULL,threadFun,&loops);
 *	flag=pthread_join(thd1,NULL);
 *	flag=pthread_create(&thd2,NULL,threadFun,&loops);
 *	flag=pthread_join(thd2,NULL);
 * 无需加锁，结果也正常。
 *
 * 运行指令
 * gcc 7.07.02.c -o temp -Wall -std=c11 -lpthread
 */
