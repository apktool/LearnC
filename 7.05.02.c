/**
 * @file 7.05.02.c
 * @brief fork(),vfork(),clone()
 * @author LiWenGang
 * @date 2016-07-05
 */
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

void fork_Proccess();
void vfork_Proccess();
pid_t vfork(void);

int main(int argc, char* argv[]){
	fork_Proccess();
	vfork_Proccess();
	return 0;
}

void fork_Proccess(){
	int cnt=0;
	int status;
	pid_t pid;
	pid=fork();
	switch(pid){
		case -1:perror("error\n");
				exit(EXIT_FAILURE);
				break;
		case  0:cnt++;
				printf("I am fork child.|cnt=%d|pid=%d\n",cnt,getpid());
				_exit(EXIT_SUCCESS);
				break;
		default:waitpid(-1,&status,SIGCHLD);
				printf("I am fork father.|cnt=%d|pid=%d\n",cnt,getpid());
				exit(EXIT_SUCCESS);
				break;
	}
}

void vfork_Proccess(){
	int cnt=0;
	int status;
	pid_t pid;
	pid=vfork();
	switch(pid){
		case -1:perror("error\n");exit(-1);break;
		case  0:cnt++;
				printf("I am vfork child.|cnt=%d|pid=%d\n",cnt,getpid());
				_exit(EXIT_SUCCESS);
				break;
		default:waitpid(-1,&status,SIGCHLD);
				printf("I am vfrok father.|cnt=%d|pid=%d\n",cnt,getpid());
				exit(EXIT_SUCCESS);
				break;

	}
}

/*
 * fork创建一个进程时，子进程只是完全复制父进程的资源，复制出来的子进程有自己的task_struct结构和pid,但却复制父进程其它所有的资源。
 * 例如，要是父进程打开了五个文件，那么子进程也有五个打开的文件，而且这些文件的当前读写指针也停在相同的地方。
 *
 * vfork创建的子进程与父进程共享地址空间，也就是说子进程完全运行在父进程的地址空间上，如果这时子进程修改了某个变量，这将影响到父进程。
 *
 *  fork是进程资源的完全复制，包括进程的 PCB、进程的系统堆栈、进程的用户空间、进程打开的设备等。而在clone中其实只有前两项是被复制了的，后两项都与父进程共享。
 */ 
