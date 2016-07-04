/**
 * @file 7.04.01.c
 * @brief stdio缓冲区重定向所导致的错误
 * @author LiWenGang
 * @date 2016-07-04
 */
#include<sys/types.h>
#include<sys/unistd.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<stdio.h>

int main(int argc, char* argv[]){
	int fd;
	fd=open("123.txt",O_RDWR|O_CREAT,S_IWUSR|S_IRUSR);
	if(fd==-1){
		printf("error open\n");
	}

	printf("Hello world\n");
	
	pid_t pid=fork();
	switch(pid){
		case -1:printf("error fork");break;
		case 0 :_exit(0);break;
		default:if(wait(NULL)==-1){
					printf("error wait\n");
				}
				break;
	}

	return 0;
}
/*
 * 进程的用户空间内存中会维护stdio缓冲区，因此通过fork()创建子进程时会复制这些缓冲区。
 * 1.当标准输出定向到终端时，因为缺省为行缓冲，所以会立即显示函数printf()输出的包含换行符的字符串。
 * 2.当标准输出重定向到文件时，由于缺省为块缓冲，父子进程调用exit()时会刷新各自的stdio缓冲区，从而导致重复的输出结果。
 * 解决方案：
 * 1.调用fork()之前使用fflush()刷新stdio缓冲区或者使用setvbuf()和setbuf()关闭stdio流的缓冲功能
 * 2.子进程条用_exit()而非exit()，以便不再刷新stdio缓冲区。父进程调用exit()终止
 */
