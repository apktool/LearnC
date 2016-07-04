/**
 * @file 7.04.06.c
 * @brief 僵尸进程
 * @author LiWenGang
 * @date 2016-07-04
 */
#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char* argv[]){
	pid_t pid;
	pid=fork();
	switch(pid){
		case -1:perror("error fork");
				exit(EXIT_FAILURE);
				break;
		case  0:printf("I am child\n");
				exit(EXIT_SUCCESS);
				break;
		default:printf("I am father\n");
				sleep(2);
				system("ps -o pid,ppid,state,tty,command");
				printf("father proccess is exiting\n");
	}
}

/*
 * 僵尸进程：
 * 父进程使用fork创建子进程，如果子进程退出，而父进程并没有调用wait()或waitpid()获取子进程的状态信息，那么子进程的进程描述符仍然保存在系统中，这种进程称为僵尸进程。
 * 导致的问题：
 * 如果进程不调用wait()/waitpid()的话，那么保留的那段信息就不会被释放，其进程号就会一直被占用，但是系统所能使用的进程号是有限的，如果产生大量的僵尸进程，将因为没有可用的进程号而导致系统不能产生新的进程，此即为僵尸进程的危害，应当避免。
 * 任何一个子进程(除init之外)在exit()之后，并非马上消息掉，会留下一个名为僵尸进程(Zombie)的数据结构，等待父进程处理。ps查看进程会得到<defunct>的标识。
 */

