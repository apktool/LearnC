/**
 * @file 10.09.01.c
 * @brief setbuf|关联缓冲区与流
 * @author LiWenGang
 * @date 2016-10-09
 */
#include<stdio.h>

int main(int argc, char* argv[]){
	char outbuf[50];

	setbuf(stdout,outbuf);//将outbuf与stdout绑定起来

	fputs("hello world\n",stdout);
	fputs(outbuf,stdout);

	fflush(stdout);//刷新stdout流，不然会影响下次程序的运行结果
	return 0;
}
