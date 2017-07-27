/**
 * @file 7.27.01.c
 * @Synopsis  结构体数组，结构体指针
 * @author apktool
 * @version 0.1
 * @date 2017-07-27
 */
#include<stdio.h>

struct desc_struct{
	unsigned long a;
	unsigned long b;
};

typedef struct desc_struct desc_table[4];

int main(int argc, char* argv[]){
	struct desc_struct *p;
	desc_table gdt;

	p=gdt;
	p->a=1;

	printf("%lu\n", p->a);
	printf("%lu\n", gdt->a);

	/*--------------------*/

	p=gdt+4;
	p->b=5;

	printf("%lu\n", p->b);
	printf("%lu\n", (gdt+4)->b);

	return 0;
}

/*
 * 本程序运行会出现下述错误
 *
 * *** stack smashing detected ***
 *
 * 个人一开始认为是p=gdt+4出现了错误，但是如果把4改成其它数值却不会报错
 * 有点不太明白
 *
 * 个人认为这里的gdt可以认为是desc_table[4]
 * gdt+4 应当等价于 desc_table[4]，即获取desc_table的第4个元素(从0开始计数)
 * 而desc_table共4个元素，而desc_table[4]属于越界
 *
 * 但是疑问在于如果这里的gdt+4改成gdt+8却仍然正确，不太明白
 */
