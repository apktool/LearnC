/**
 * @file 7.04.04_01.c
 * @brief execve() 配合7.04.04_02.c使用
 * @author LiWenGang
 * @date 2016-07-04
 */
#include<stdio.h>

int main(int argc,char* argv[]){
	for(int i=0;i<argc;i++){
		printf("argv[%d]:%s\n",i, argv[i]);
	}
	return 0;
}

/*
 * gcc 7.04.04_01.c -o temp1 -Wall -std=c11
 * ./temp2 ./temp1
 */
