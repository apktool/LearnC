/**
 * @file 10.12.01.c
 * @brief errno
 * @author LiWenGang
 * @date 2016-10-12
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char* argv[]){
	for(int i=0;i<256;i++){
		printf("errno. %03d is: %s\n",i,strerror(i));
	}
}
