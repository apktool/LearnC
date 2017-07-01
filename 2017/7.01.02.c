/**
 * @file 7.01.02.c
 * @Synopsis  函数指针,指针函数
 * @author apktool
 * @version 0.1
 * @date 2017-07-01
 */
#include<stdio.h>

void (*fun1)(void);  // 函数指针：即本身是一个指针，指向一个函数
void haha1(void);

void *fun2(void);    // 指针函数：即本身一个函数，返回一个指针

int main(int argc, char* argv[]){
	fun1=haha1;
	fun1();

	void* haha2=fun2();
	printf("%p\n", haha2);
	return 0;
}

void haha1(void){
	printf("hello world\n");
}

void* fun2(void){
	int a=2;
	int* p=&a;
	return p;
}
