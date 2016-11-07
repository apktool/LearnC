/**
 * @file 11.06.02.c
 * @brief 回射服务器|客户端
 * @author LiWenGang
 * @date 2016-11-07
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

ssize_t writen(int fd, const void* buf, size_t count);
ssize_t readn(int fd, const void* buf, size_t count);
ssize_t readline(int sockfd, void *buf, size_t maxline);
ssize_t recv_peek(int sockfd, void *buf, size_t len);

int main(int argc, char* argv[]){
	int listenfd;
	listenfd=socket(AF_INET,SOCK_STREAM,0);
	assert(listenfd!=-1);

	struct sockaddr_in client;
	memset(&client,0,sizeof(client));
	client.sin_family=AF_INET;
	client.sin_port=htons(5588);
	client.sin_addr.s_addr=inet_addr("127.0.0.1");

	int flag;
	flag=connect(listenfd,(struct sockaddr*)&client,sizeof(client));
	assert(flag!=-1);

	char sendbuf[1024];
	char recvbuf[1024];
	while(fgets(sendbuf,sizeof(sendbuf),stdin)!=NULL){
		writen(listenfd,sendbuf,sizeof(sendbuf));
		int ret=readline(listenfd,recvbuf,sizeof(recvbuf));
		assert(ret!=-1);
		if(ret==0){
			perror("client close!");
			break;
		}
		fputs(recvbuf,stdout);
		memset(sendbuf,0,sizeof(sendbuf));
		memset(sendbuf,0,sizeof(recvbuf));
	}

	close(listenfd);
	return 0;
}

ssize_t readn(int fd, const void* buf, size_t count){
	size_t nleft=count;
	ssize_t nread;	
	char* bufp=(char*)buf;
	while(nleft>0){
		if((nread=read(fd,bufp,nleft))<0){
			if(errno==EINTR){
				continue;
			}
			return -1;
		}
		if(nread==0){
			break;
		}
		bufp+=nread;
		nleft-=nread;
	}
	return count-nleft;
}

ssize_t writen(int fd, const void* buf, size_t count){
	size_t nleft=count;
	ssize_t nwrite;	
	char* bufp=(char*)buf;
	while(nleft>0){
		if((nwrite=write(fd,bufp,nleft))<0){
			if(errno==EINTR){
				continue;
			}
			return -1;
		}
		if(nwrite==0){
			break;
		}
		bufp+=nwrite;
		nleft-=nwrite;
	}
	return count-nleft;
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

ssize_t recv_peek(int sockfd, void *buf, size_t len){
	while(1){
		int ret=recv(sockfd,buf,len,MSG_PEEK);//读取缓存区中的数据，但是并不清零，这点与read不一样，read读取完成后会清空缓冲区
		if(ret==-1&&errno==EINTR){//被信号中断
			continue;
		}
		return ret;
	}
}
