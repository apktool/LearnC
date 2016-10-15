/**
 * @file 10.15.03.c
 * @brief sock编程|回射客户/服务器
 * @author LiWenGang
 * @date 2016-10-15
 */
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
#include<assert.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//extern uint16_t htons(uint16_t hostshort);

int main(int argc, char* argv[]){
	int listenfd;
	listenfd=socket(AF_INET,SOCK_STREAM,0);
	assert(listenfd!=-1);

	struct sockaddr_in servaddr;
	memset(&servaddr,0,sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(5188);
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
//	servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
//	inet_aton("127.0.0.1",&servaddr.sin_addr);
	
	int flag;
	flag=bind(listenfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
	assert(flag!=-1);

	flag=listen(listenfd,SOMAXCONN);
	assert(flag!=-1);

	struct sockaddr_in peeraddr;
	socklen_t peerlen=sizeof(peeraddr);
	int conn;
	conn=accept(listenfd,(struct sockaddr*)&peeraddr,&peerlen);//主动套接字
	assert(conn!=-1);

	char recvbuf[1024];
	while(1){
		memset(recvbuf,0,sizeof(recvbuf));
		int ret=read(conn,recvbuf,sizeof(recvbuf));
		fputs(recvbuf,stdout);
		write(conn,recvbuf,ret);
	}
	close(conn);
	close(listenfd);
	return 0;
}

/*
 * 主动套接字：会调用connect函数发起连接
 * 被动套接字：会调用accept函数接收连接
 */

/*
 * 配合10.15.04.c使用，让本程序做服务器，10.15.04.c做客户端。
 */
