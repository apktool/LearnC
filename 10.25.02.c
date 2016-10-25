/**
 * @file 10.25.02.c
 * @brief 点到点通信
 * @author LiWenGang
 * @date 2016-10-25
 */
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<assert.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<signal.h>

void handler(int sig);

int main(int argc, char* argv[]){
	int listenfd;
	listenfd=socket(AF_INET,SOCK_STREAM,0);
	assert(listenfd!=-1);

	struct sockaddr_in client;
	client.sin_family=AF_INET;
	client.sin_port=htons(5588);
	client.sin_addr.s_addr=inet_addr("127.0.0.1");

	int flag;
	flag=connect(listenfd,(struct sockaddr*)&client,sizeof(client));
	assert(flag!=-1);

	char sendbuf[1024];
	char recvbuf[1024];
	pid_t pid;
	pid=fork();
	switch(pid){
		case -1:perror("error pid");
				break;
		case  0:while(1){
					memset(recvbuf,0,sizeof(recvbuf));
					int ret=read(listenfd,recvbuf,sizeof(recvbuf));
					assert(ret!=-1);
					if(ret==0){
						printf("error close\n");
						break;
					}
					fputs(recvbuf,stdout);
				}
				kill(getppid(),SIGUSR1);
				_exit(EXIT_SUCCESS);
				break;
		default:while(fgets(sendbuf,sizeof(sendbuf),stdin)!=NULL){
					write(listenfd,sendbuf,sizeof(sendbuf));
					read(listenfd,recvbuf,sizeof(recvbuf));
					fputs(recvbuf,stdout);
					memset(sendbuf,0,sizeof(sendbuf));
					memset(recvbuf,0,sizeof(recvbuf));
				}
				exit(EXIT_SUCCESS);
				break;
	}

	return 0;
}

void handler(int sig){
	printf("recv a sig=%d\n",sig);
	exit(EXIT_SUCCESS);
}
/*
 * 本程序与10.25.01.c配合使用，将本程序作为客户端，10.25.01.c作为服务器，实现点到点通信
 * gcc 10.25.02.c -o a2.out -Wall -std=c11 -D_POSIX_C_SOURCE
 */
