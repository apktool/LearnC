/**
 * @file 10.29.02.c
 * @brief 粘包问题|客户端
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

ssize_t readn(int fd, void *buf, size_t count);
ssize_t writen(int fd, const void *buf, size_t count);

struct packet{
	int len;
	char buf[1024];
};

int main(int argc, char* argv[]){
	int listenfd;
	listenfd=socket(AF_INET,SOCK_STREAM,0);
	assert(listenfd!=-1);

	struct sockaddr_in client_addr;
	memset(&client_addr,0,sizeof(client_addr));
	client_addr.sin_family=AF_INET;
	client_addr.sin_port=htons(5588);
	client_addr.sin_addr.s_addr=inet_addr("127.0.0.1");

	int flag;
	flag=connect(listenfd,(struct sockaddr*)&client_addr,sizeof(client_addr));
	assert(flag!=-1);

	struct packet sendbuf;
	struct packet recvbuf;
	memset(&sendbuf,0,sizeof(sendbuf));
	memset(&recvbuf,0,sizeof(recvbuf));
	
	int nlen;
	int ret;
	while(fgets(sendbuf.buf,sizeof(sendbuf),stdin)!=NULL){
		nlen=strlen(sendbuf.buf);
		sendbuf.len=htonl(nlen);
		writen(listenfd,&sendbuf,4+nlen);//包头4个字节+包体字节

		ret=readn(listenfd,&recvbuf.len,4);
		assert(ret!=-1);
		if(ret<4){
			perror("client quit");
			break;
		}

		nlen=ntohl(recvbuf.len);
		ret=readn(listenfd,recvbuf.buf,nlen);
		assert(ret!=-1);
		if(ret<nlen){
			perror("client quit");
			break;
		}

		fputs(recvbuf.buf,stdout);
		memset(&sendbuf.buf,0,sizeof(sendbuf));
		memset(&recvbuf.buf,0,sizeof(recvbuf));
	}

	close(listenfd);
	return 0;
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
 * 本程序采用“包头加上包体长度的方法解决粘包问题”
 */
