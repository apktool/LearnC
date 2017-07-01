/**
 * @file 9.12.01.c
 * @brief 位移|>>
 * @author LiWenGang
 * @date 2016-09-12
 */
#include<stdio.h>

#define BitGet(Number,Pos) (Number>>Pos)

int main(int argc, char* argv[]){
	int pos=BitGet(8,3);
	if(!pos){
		printf("=0\n");
	}else{
		printf("%d\n",pos);
	}
	return 0;
}
