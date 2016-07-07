/**
 * @file 7.07.01.c
 * @brief pthread_creat(),pthread_join()
 * @author LiWenGang
 * @date 2016-07-07
 */
#include<sys/types.h>
#include<pthread.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

static void* threadFunc(void* arg);

int main(int argc, char* argv[]){
	pthread_t t1;
	void *res;
	int s;

	s=pthread_create(&t1,NULL,threadFunc,"Hello world\n");
	if(s!=0){
		perror("error pthread_creat");
	}
	printf("Message from main()\n");
	s=pthread_join(t1,&res);
	if(s!=0){
		perror("error pthread_join");
	}
	printf("Thread returned %ld\n",(long)res);
	return 0;
}

static void* threadFunc(void* arg){
	char* s=(char*)arg;
	printf("%s",s);
	return (void*)strlen(s);
}
