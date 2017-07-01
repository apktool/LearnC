/**
 * @file 7.05.01.c
 * @brief  acct|进程记账
 * @author LiWenGang
 * @date 2016-07-05
 */
#include<unistd.h>
#include<stdio.h>

int acct(const char *filename);

int main(int argc, char* argv[]){
	if(acct(argv[1])==-1){
		printf("acct\n");
	}
	printf("Process accounting %s\n",(argv[1]==NULL)?"disabled":"enabled");
	return 0;
}

/*
 * 一旦打开进程记账功能，每当一个进程终止时，就会有一条记账信息写入系统级的进程记账文件
 * 1.特权进程可利用系统嗲用acct()来打开和关闭进程记账功能
 * 2.应用程序很少使用这一系统调用/。
 */
