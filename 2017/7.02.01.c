/**
 * @file 7.02.01.c
 * @Synopsis  printf 返回值
 * @author apktool
 * @version 0.1
 * @date 2017-07-02
 */

#include<stdio.h>

int main(int argc, char* argv[]){
	int a=43;
	printf("%d\n", printf("%d", printf("%d", a)));
	return 0;
}

/**
 * man 3 printf:
 * Upon successful return, these functions  return  the  number  of  characters  printed
 * (excluding the null byte used to end output to strings).
 */
