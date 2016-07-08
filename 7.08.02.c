/**
 * @file 7.08.02.c
 * @brief enum|枚举类型
 * @author LiWenGang
 * @date 2016-07-08
 */
#include<stdio.h>
#include<string.h>

enum spectrum{
	red,orange,yellow,green,blue,violet
}color;

int main(int argc, char* argv[]){
	const char* value[]={"red","orange","yellow","green","blue","violet"};

	char ch[]="green";

	for(color=red;color<=violet;color++){
		if(strcmp(ch,value[color])==0){
			printf("%s is found\n",ch);
		}
	}
	return 0;
}
/*
 *  因为枚举类型是一个整数类型，所以enum变量能够像整数变量那样被使用在表达式中。
 */ 
