/**
 * @file 10.25.01.c
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

void do_service(int conn);
void handler(int sig);

int main(int argc, char* argv[]){
	int listenfd;
	listenfd=socket(AF_INET,SOCK_STREAM,0);
	assert(listenfd!=-1);

	struct sockaddr_in server;
	server.sin_family=AF_INET;
	server.sin_port=htons(5588);
	server.sin_addr.s_addr=htonl(INADDR_ANY);

	int on=1;
	if(setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on))<0){
		printf("setsockopt!\n");
	}

	int flag;
	flag=bind(listenfd,(struct sockaddr*)&server,sizeof(server));
	assert(flag!=-1);

	flag=listen(listenfd,SOMAXCONN);
	assert(flag!=-1);

	struct sockaddr_in peeraddr;
	socklen_t addrlen=sizeof(peeraddr);
	int conn;
	pid_t pid;

	conn=accept(listenfd,(struct sockaddr*)&peeraddr,&addrlen);
	assert(conn!=-1);
	printf("ip=%s port=%d\n",inet_ntoa(peeraddr.sin_addr),peeraddr.sin_port);

	char sendbuf[1024]={0};
	char recvbuf[1024]={0};
	pid=fork();
	switch(pid){
		case -1:perror("error fork");
				break;
		case  0:signal(SIGUSR1,handler);
				while(fgets(sendbuf,sizeof(sendbuf),stdin)!=NULL){
					write(conn,sendbuf,strlen(sendbuf));
					memset(recvbuf,0,sizeof(recvbuf));
				}
				_exit(EXIT_SUCCESS);
				break;
		default:while(1){
					int ret=read(conn,recvbuf,sizeof(recvbuf));
					assert(ret!=-1);
					if(ret==0){
						printf("peer close\n");
						break;
					}
					fputs(recvbuf,stdout);
				}
				kill(pid,SIGUSR1);
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
 * 本程序与10.25.02.c配合使用，将本程序作为服务器，10.25.02.c作为客户端，实现点到点通信
 * gcc 10.25.01.c -o a1.out -Wall -std=c11 -D_POSIX_C_SOURCE
 */
