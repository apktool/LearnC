/**
 * @file 10.29.01.c
 * @brief 粘包问题|服务器端
 * @author LiWenGang
 * @date 2016-10-29
 */

#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<assert.h>
#include<errno.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct packet{
	int len;
	char buf[1024];
};

void do_service(int conn);
ssize_t readn(int fd, void *buf, size_t count);
ssize_t writen(int fd, const void *buf, size_t count);

int main(int argc, char* argv[]){
	int listenfd;
	listenfd=socket(AF_INET,SOCK_STREAM,0);
	assert(listenfd!=-1);

	struct sockaddr_in server_addr;
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(5588);
	server_addr.sin_addr.s_addr=htonl(INADDR_ANY);

	int flag;
	flag=bind(listenfd,(struct sockaddr*)&server_addr,sizeof(server_addr));
	assert(flag!=-1);

	flag=listen(listenfd,SOMAXCONN);
	assert(flag!=-1);

	struct sockaddr_in peer_addr;
	socklen_t peerlen=sizeof(peer_addr);
	int conn;
	pid_t pid;
	while(1){
		conn=accept(listenfd,(struct sockaddr*)&peer_addr,&peerlen);
		assert(conn!=-1);
		printf("ip=%s\tport=%d\n",inet_ntoa(peer_addr.sin_addr),peer_addr.sin_port);

		pid=fork();
		switch(pid){
			case -1:perror("fork error");
					break;
			case  0:do_service(conn);
					close(conn);
					_exit(EXIT_SUCCESS);
					break;
			default:
					//exit(EXIT_SUCCESS);
					break;
		}
	}
	close(listenfd);
	return 0;
}

void do_service(int conn){
	struct packet recvbuf;
	int ret;
	int nlen;
	while(1){
		memset(&recvbuf,0,sizeof(recvbuf));
		ret=readn(conn,&recvbuf.len,4);
		assert(ret!=-1);
		if(ret<4){
			printf("client quit");
			break;
		}

		nlen=ntohl(recvbuf.len);
		ret=readn(conn,recvbuf.buf,nlen);
		assert(ret!=-1);
		if(ret<4){
			printf("client quit");
			break;
		}

		fputs(recvbuf.buf,stdout);
		writen(conn,&recvbuf,4+nlen);
	}
}

ssize_t readn(int fd, void *buf, size_t count){
	size_t nleft=count;
	ssize_t nread;
	char* bufp=(char*)buf;
	while(nleft>0){
		if((nread=read(fd,bufp,nleft))<0){
			if(errno==EINTR){//被信号中断
				continue;
			}
			return -1;
		}else if(nread==0){//对等方关闭
			return count-nleft;//已读字节数=全部字节数-剩余字节数
		}

		bufp+=nread;
		nleft-=nread;//剩余字节数
	}
	return count;
}

ssize_t writen(int fd, const void *buf, size_t count){
	size_t nleft=count;//剩余要发送的字节数
	ssize_t nwritten;
	char* bufp=(char*)buf;
	while(nleft>0){
		if((nwritten=write(fd,bufp,nleft))<0){
			if(errno==EINTR){//被信号中断
				continue;
			}
			return -1;
		}else if(nwritten==0){//对等方关闭
			return count-nleft;//已读字节数=全部字节数-剩余字节数
		}

		bufp+=nwritten;
		nleft-=nwritten;//剩余字节数
	}
	return count;
	
}
/*
 * TCP发送的是字节流，无边界
 * UDP发送的是消息，由边界
 *
 * 粘包产生的原因有很多。
 * 比如当应用进程缓冲区的大小比套接口缓冲区的大小大时，若数据需要发送，从应用进程缓冲区拷贝到套接口缓冲区会导致一次拷贝不完，原来应用进程缓冲区的数据就会一部分被发送出去，被对方接收，而另一部分却未被发送，连同下一次消息一起被发送出去，造成粘包问题
 *
 * 粘包问题的解决方案：
 * 	定长包
 * 	包尾加\r\n(ftp就是这么干的)
 * 	包头加上包体长度
 * 	更复杂的应用层协议
 */
