/**
 * @file 10.15.04.c
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
	int sock;
	sock=socket(AF_INET,SOCK_STREAM,0);
	assert(sock!=-1);

	struct sockaddr_in servaddr;
	memset(&servaddr,0,sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(5188);
//	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
//	inet_aton("127.0.0.1",&servaddr.sin_addr);
	
	int flag;
	flag=connect(sock,(struct sockaddr*)&servaddr,sizeof(servaddr));
	assert(flag!=-1);

	char sendbuf[1024]={0};
	char recvbuf[1024]={0};
	while(fgets(sendbuf,sizeof(sendbuf),stdin)!=NULL){
		write(sock,sendbuf,strlen(sendbuf));
		read(sock,recvbuf,sizeof(recvbuf));
		fputs(recvbuf,stdout);
		memset(sendbuf,0,sizeof(sendbuf));
		memset(recvbuf,0,sizeof(recvbuf));
	}
	close(sock);


	return 0;
}

/*
 * 主动套接字：会调用connect函数发起连接
 * 被动套接字：会调用accept函数接收连接
 */
/*
 * 配合10.15.03.c使用，让本程序做客户端，10.15.04.c做服务器。
 */
