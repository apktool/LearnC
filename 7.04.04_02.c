/**
 * @file 7.04.04_02.c
 * @brief execve() 配合7.04.04_01.c使用
 * @author LiWenGang
 * @date 2016-07-04
 */
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc, char* argv[]){
	char* newargv[]={"NULL","hello","world",NULL};
	char* newenviron[]={NULL};
	if(argc!=2){
		fprintf(stderr,"Usage: %s <file-to-exec>\n",argv[0]);
		exit(EXIT_FAILURE);
	}

	newargv[0]=argv[1];
	execve(argv[1],newargv,newenviron);
	perror("execve");
	exit(EXIT_FAILURE);
}

/*
 * gcc 7.04.04_02.c -o temp -Wall -std=c11
 * ./temp2 ./temp1
 */
