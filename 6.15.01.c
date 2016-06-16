//函数式宏定义，回调函数
#include<stdio.h>

#define AbNoraml(W) (Sgn((W)))

static int Sgn(int);
typedef int (*CompFunc)(int,int);

static int Find(CompFunc CmpFunc){
	int tmp=AbNoraml(CmpFunc(6,4));
	return tmp;
}

static int Sgn(int x){
	return x==0?0:(x>0?1:-1);
}

int Sum(int x, int y){
	return x-y;
}

int main(int argc,char* argv[]){
	CompFunc tmp=Sum;
	int value=Find(tmp);
	printf("%d\n",value);
	return 0;
}
