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

void do_service(int conn);

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
	
	/*
	 * 为了防止因为退出服务器端退出登陆，因为socket被占用而不能继续登陆的问题
	 * netstat -an | grep TIME_WAIT
	 */
	int on;
	if(setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on))<0){
		perror("error setsockopt!");
	}
	
	int flag;
	flag=bind(listenfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
	assert(flag!=-1);

	flag=listen(listenfd,SOMAXCONN);
	assert(flag!=-1);

	struct sockaddr_in peeraddr;
	socklen_t peerlen=sizeof(peeraddr);
	int conn;

	/*
	 * 解决只能为一个客户端服务的问题
	 */
	pid_t pid;
	while(1){

		conn=accept(listenfd,(struct sockaddr*)&peeraddr,&peerlen);//主动套接字
		assert(conn!=-1);
		printf("ip=%s\tport=%d\n",inet_ntoa(peeraddr.sin_addr),peeraddr.sin_port);

		pid=fork();
		switch(pid){
			case -1:perror("error fork");
					break;
			case  0:close(listenfd);
					do_service(conn);
					_exit(EXIT_SUCCESS);
					break;
			default:close(conn);
					break;
		}
	}
	return 0;
}

void do_service(int conn){
	char recvbuf[1024];
	while(1){
		memset(recvbuf,0,sizeof(recvbuf));
		int ret=read(conn,recvbuf,sizeof(recvbuf));
		assert(ret!=-1);
		/*
		 * 捕捉客户端退出
		 */
		if(ret==0){
			printf("client close\n");
			break;
		}
		fputs(recvbuf,stdout);
		write(conn,recvbuf,ret);
	}
}

/*
 * 主动套接字：会调用connect函数发起连接
 * 被动套接字：会调用accept函数接收连接
 */

/*
 * 配合10.15.04.c使用，让本程序做服务器，10.15.04.c做客户端。
 */
