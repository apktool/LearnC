/**
 * @file 10.30.01.c
 * @brief 粘包问题readline|服务器端
 * @author LiWenGang
 * @date 2016-10-30
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

void do_service(int conn);
ssize_t readn(int fd, void *buf, size_t count);
ssize_t writen(int fd, const void *buf, size_t count);
ssize_t recv_peek(int sockfd, void *buf, size_t len);
ssize_t readline(int sockfd, void *buf, size_t len);

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
	char recvbuf[1024];
	int ret;
	while(1){
		memset(&recvbuf,0,sizeof(recvbuf));
		ret=readn(conn,recvbuf,4);
		assert(ret!=-1);
		if(ret==0){
			printf("client quit");
			break;
		}

		fputs(recvbuf,stdout);
		writen(conn,&recvbuf,strlen(recvbuf));
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

ssize_t recv_peek(int sockfd, void *buf, size_t len){
	while(1){
		int ret=recv(sockfd,buf,len,MSG_PEEK);//读取缓存区中的数据，但是并不清零，这点与read不一样，read读取完成后会清空缓冲区
		if(ret==-1&&errno==EINTR){//被信号中断
			continue;
		}
		return ret;
	}
}

ssize_t readline(int sockfd, void *buf, size_t maxline){//使用recv函数实现readline功能
		int ret;
		int nread;
		char* bufp=buf;
		int nleft=maxline;
		while(1){
			ret=recv_peek(sockfd,bufp,nleft);//读取缓存区中的数据。
			if(ret<=0){
				return ret;
			}
			nread=ret;
			for(int i=0;i<nread;i++){
				if(bufp[i]=='\n'){
					ret=readn(sockfd,bufp,i+1);
					if(ret!=i+1){
						exit(EXIT_FAILURE);
					}
					return ret;
				}
			}
			if(nread>nleft){
				exit(EXIT_FAILURE);
			}
			nleft-=nread;
			ret=readn(sockfd,bufp,nread);
			if(ret!=nread){
				exit(EXIT_FAILURE);
			}
			buf+=nread;
		}
		return -1;
}
