/**
 * @file 7.07.01.c
 * @brief pthread_creat(),pthread_join(),pthread_exit()
 * @author LiWenGang
 * @date 2016-07-07
 */

#include<sys/types.h>
#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

static void* pthreadFun(void*);

int main(int argc, char* argv[]){
	pthread_t thd;
	void* s;
	int flag;

	flag=pthread_create(&thd,NULL,pthreadFun,"hello world");
	if(flag!=0){
		perror("error pthread create");
	}
	printf("this message from main()\n");
	flag=pthread_join(thd,&s);
	if(flag!=0){
		perror("error pthread join");
	}
	printf("%ld\n",(long int)s);
	pthread_exit(s);
	return 0;
}

static void* pthreadFun(void* s){
	char* str=(char*)s;
	puts(str);
	return (void*)strlen(str);
}
