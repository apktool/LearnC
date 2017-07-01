/**
 * @file 6.29.05.c
 * @brief alarm()
 * @author LiWenGang
 * @date 2016-06-29
 */
#include<stdio.h>
#include<unistd.h>

int main(int argc,char* argv[]){
	alarm(1);
	for(int i=0;1;i++){
		printf("count=%d\t",i);
	}
	return 0;
}
