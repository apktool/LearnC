/**
 * @file 10.15.01.c
 * @brief 验证字节序|小端序
 * @author LiWenGang
 * @date 2016-10-15
 */
#include<stdio.h>

int main(int argc, char* argv[]){
	unsigned int x=0x12345678;
	unsigned char* p=(unsigned char*)&x;

	printf("%0x %0x %0x %0x\n",p[0],p[1],p[2],p[3]);
	return 0;
}

/*
 * 大端字节序：最高有效位存储与最低内存地址处，最低有效位存储于最高内存地址处
 * 小端字节序：最高有效位存储于最高内存地址处，最低有效位存储于最低内存地址处
 */
