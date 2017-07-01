/**
 * @file 8.23.01.c
 * @brief strtod
 * @author LiWenGang
 * @date 2016-08-23
 */
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char* argv[]){
	char str[]="   365.24abc";
	char* pend=NULL;
	double d1;
	d1=strtod(str,&pend);
	printf("%f\n",d1);
	printf("%s\n",pend);
	return 0;
}

/*
 * ANSI C 规范定义了 stof()、atoi()、atol()、strtod()、strtol()、strtoul() 共6个可以将字符串转换为数字的函数；
 * 使用 strtod(str, NULL) 与使用 atof() 结果相同。
 * 另外在 C99 / C++11 规范中又新增了5个函数，分别是 atoll()、strtof()、strtold()、strtoll()、strtoull()。
 */
