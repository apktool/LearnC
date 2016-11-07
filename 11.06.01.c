/**
 * @file 11.06.01.c
 * @brief 回射服务器（避免僵尸进程）|服务器端
 * @author LiWenGang
 * @date 2016-11-07
 */
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/wait.h>
#include<arpa/inet.h>
#include<signal.h>
#include<unistd.h>
#include<assert.h>
#include<errno.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void do_service(int sockfd);
ssize_t writen(int fd, const void* buf, size_t count);
ssize_t readn(int fd, const void* buf, size_t count);
ssize_t readline(int sockfd, void *buf, size_t maxline);
ssize_t recv_peek(int sockfd, void *buf, size_t len);
void handle_sigchild(int sig);


int main(int argc, char* argv[]){
	//signal(SIGCHLD, SIG_IGN);//通过信号量来避免产生僵尸进程。
	signal(SIGCHLD,handle_sigchild);

	int listenfd;
	listenfd=socket(AF_INET,SOCK_STREAM,0);
	assert(listenfd!=-1);

	struct sockaddr_in server;
	memset(&server,0,sizeof(server));
	server.sin_family=AF_INET;
	server.sin_port=htons(5588);
	server.sin_addr.s_addr=htonl(INADDR_ANY);

	int flag;
	flag=bind(listenfd,(struct sockaddr*)&server,sizeof(server));
	assert(flag!=-1);

	flag=listen(listenfd,SOMAXCONN);
	assert(flag!=-1);

	int sockfd;
	struct sockaddr_in addrfd;
	socklen_t addrlen=sizeof(addrfd);

	pid_t pid;

	while(1){
		sockfd=accept(listenfd,(struct sockaddr*)&addrfd,&addrlen);
		assert(sockfd!=-1);
		printf("ip: %s | %d\n",inet_ntoa(addrfd.sin_addr),ntohs(addrfd.sin_port));

		pid=fork();
		switch(pid){
			case -1:perror("error fd");
					break;
			case  0:close(listenfd);
					do_service(sockfd);
					_exit(EXIT_SUCCESS);
					break;
			default:close(sockfd);
					//exit(EXIT_SUCCESS);
					break;
		}
	}

	close(sockfd);
	close(listenfd);
	return 0;
}

void do_service(int sockfd){
	char recvbuf[1024];
	while(1){
		memset(recvbuf,0,sizeof(recvbuf));
		int ret=readn(sockfd,recvbuf,sizeof(recvbuf));
		assert(ret!=-1);
		if(ret==0){
			printf("client close\n");
			break;
		}
		fputs(recvbuf,stdout);
		writen(sockfd,recvbuf,ret);
	}
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

void handle_sigchild(int sig){
	wait(NULL);
}
