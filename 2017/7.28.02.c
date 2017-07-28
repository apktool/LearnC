/**
 * @file 7.28.02.c
 * @Synopsis  struct, union
 * @author apktool
 * @version 0.1
 * @date 2017-07-28
 */
#include<stdio.h>

struct test1{
	char mark;
	long num;
	float score;
}a;

union test2{
	char mark;
	long num;
	float score;
}b;

int main(int argc, char* argv[]){
	printf("%lu\n", sizeof(a));
	printf("%lu\n", sizeof(b));
	printf("------------------------\n");

	b.mark='b';
	printf("%c\n", b.mark);
	printf("%ld\n", b.num);
	printf("%f\n", b.score);
	printf("------------------------\n");

	printf("%p <-> %p <-> %p <-> %p\n", &b, &b.mark, &b.num, &b.score);
	return 0;
}

/*
 * 结构体struct所占用的内存为各个成员的占用的内存之和
 * 联合体union变量所占用的内存长度等于最长的成员的内存长度
 * 以上均需要考虑内存对齐的问题
 *
 * 由于union中的所有成员起始地址都是一样的，所以&a.mark、&a.num和&a.score的值都是一样的。
 */
