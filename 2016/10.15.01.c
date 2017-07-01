/**
 * @file 10.15.01.c
 * @brief 验证，转换字节序|小端序
 * @author LiWenGang
 * @date 2016-10-15
 */
#include<arpa/inet.h>
#include<stdio.h>

int main(int argc, char* argv[]){
	unsigned int x=0x12345678;
	unsigned char* p=(unsigned char*)&x;
	printf("%0x %0x %0x %0x\n",p[0],p[1],p[2],p[3]);

	unsigned int y=htonl(x);	//将主机字节序转换为网络字节序
	p=(unsigned char*)&y;
	printf("%0x %0x %0x %0x\n",p[0],p[1],p[2],p[3]);
	return 0;
}

/*
 * 大端字节序：最高有效位存储与最低内存地址处，最低有效位存储于最高内存地址处
 * 小端字节序：最高有效位存储于最高内存地址处，最低有效位存储于最低内存地址处
 *
 * 经过测试，本机采用小端字节序；而网络字节序使用大端字节序。
 * 因此使用htol()可以将字节序号转换为大端字节序
 */
