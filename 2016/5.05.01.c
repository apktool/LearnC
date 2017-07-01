#include<stdio.h>

int fun1(int, int);
typedef int (*fun)(int, int);

int main(int argc,char* argv[]){
	fun PFun=fun1;

	int a=PFun(30,5);
	printf("%d\n",a);

	//函数返回值的强制类型转换
	char ch;
	ch=(char)PFun(30,5);
	printf("%c\n",ch);
	return 0;
}

int fun1(int x, int y){
	return x+y;
}
