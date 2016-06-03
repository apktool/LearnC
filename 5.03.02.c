#include<stdio.h>

int fun1(int, int);
typedef int(*fun2)(int, int);

int main(int argc,char* argv[]){
	fun2 PFun;
	PFun=fun1;
	int tmp1=PFun(3,4);
	printf("%d\n",tmp1);

	int tmp2=fun1(3,4);
	printf("%d\n",tmp2);

	return 0;
}

int fun1(int x, int y){
	return x+y;
}
