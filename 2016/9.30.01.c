/**
 * @file 9.30.01.c
 * @brief 自己实现sizeof函数
 * @author LiWenGang
 * @date 2016-09-30
 */
#include<stdio.h>

#define sizeof_v(x) (char*)(&x+1)-(char*)(&x)//求解变量大小
#define sizeof_t(t) (size_t)((t*)0+1)//求解类型所占空间大小
#define ALIGN(v,b) ((v+b-1)&~(b-1))//二进制按b对齐，因此b必须是2的倍数

struct Empty{

};

int main(int argc, char* argv[]){
	struct Empty e;
	printf("%ld\n",sizeof_v(e));
	int n;
	printf("%ld\n",sizeof_v(n));

	printf("%ld\n",sizeof_t(struct Empty));
	printf("%ld\n",sizeof_t(int));

	printf("%d\n",ALIGN(3,16));
	printf("%d\n",ALIGN(31,16));
	printf("%d\n",ALIGN(0,16));
	printf("%d\n",ALIGN(4198,4096));
	return 0;
}
