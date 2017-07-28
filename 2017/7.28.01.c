/**
 * @file 7.28.01.c
 * @Synopsis  typedef int a[10]
 * @author apktool
 * @version 0.1
 * @date 2017-07-28
 */
#include<stdio.h>
#include<string.h>

typedef int a[10];

int main(int argc, char* argv[]){
	a b[10];  // 等价于 int b[10][10]
	memset(b,0,sizeof(b));
	printf("%lu\n", sizeof(b));

	b[5][5]=5;
	printf("%d\n", b[5][5]);
	return 0;
}
