/**
 * @file temp.c
 * @brief 函数指针，回调函数
 * @author LiWenGang
 * @date 2016-07-07
 */
#include<stdio.h>
#include<stdlib.h>

int (*fun1)(int, int);			//函数指针
typedef int (*fun2)(int, int);	//回调函数

int sum(int,int);

int main(int argc, char* argv[]){
	fun1=sum;
	printf("fun1:%d+%d=%d\n",3,4,fun1(3,4));

	fun2 PFun;
	PFun=sum;
	printf("fun2:%d+%d=%d\n",3,4,PFun(3,4));
	
	return 0;
}

int sum(int x, int y){
	return x+y;
}
