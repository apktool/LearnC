#include<stdio.h>
#define FUN(x) fun1(x,3)
int fun1(int, int);

int main(int argc,char* argv[]){
	int x=4;
	int a=FUN(x);
	printf("%d\n",a);
	return 0;
}

int fun1(int x, int y){
	return x+y;
}
