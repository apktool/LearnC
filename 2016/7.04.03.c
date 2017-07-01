/**
 * @file 7.04.03.c
 * @brief pipe|管道操作
 * @author LiWenGang
 * @date 2016-07-04
 */
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

#define MAXLEN 80

int main(int argc, char* argv[]){
	int n;
	int fd[2];
	pid_t pid;
	char buff[MAXLEN];
	if(pipe(fd)<0){
		perror("pipe\n");
		exit(EXIT_FAILURE);
	}
	pid=fork();
	switch(pid){
		case -1:perror("fork\n");break;
		case  0:close(fd[1]);
				n=read(fd[0],buff,MAXLEN);
				write(STDOUT_FILENO,buff,n);
				_exit(EXIT_SUCCESS);
				break;
		default:close(fd[0]);
				write(fd[1],"hello world\n",15);
				wait(NULL);
				exit(EXIT_SUCCESS);
	}
	return 0;
}
/*
 * pipe操作的时候，父子进程的标识符顺序不能写反，一定是从1口写入，0口写出。
 */
