/**
 * @file 10.15.02.c
 * @brief 字节序与点分十进制之间的转换|套接字类型
 * @author LiWenGang
 * @date 2016-10-15
 */
#include<arpa/inet.h>
#include<string.h>
#include<stdio.h>

int main(int argc, char* argv[]){
	unsigned long addr=inet_addr("192.168.1.100");//将点分十进制化网络字节序
	printf("addr=%u\n",ntohl(addr));

	struct in_addr ipaddr;
	ipaddr.s_addr=addr;
	printf("%s\n",inet_ntoa(ipaddr));//将大端字节序号转化为点分十进制
	return 0;
}

/*
 * 流式套接字 | SOCK_STREAM
 * 提供面向连接的，可靠的数据传输服务，数据无差错，无重复的发送，且按发送顺序接收
 * 数据报式套接字 | SOCK_DGRAM
 * 提供无连接服务。不提供无错保证，数据可能丢失或重复，并且接收顺序混乱。
 * 原始套接字 | SOCK_RAW
 */

/*
 * htons 把 unsigned short 类型从主机序转换到网络序
 * htonl 把 unsigned long  类型从主机序转换到网络序
 * ntohs 把 unsigned short 类型从网络序转换到主机序
 * ntohl 把 unsigned long  类型从网络序转到主机序
 */
