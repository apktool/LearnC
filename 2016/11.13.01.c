/**
 * @file 11.13.01.c
 * @brief readn,writen,readline|自实现
 * @author LiWenGang
 * @date 2016-11-13
 */
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#include<assert.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

ssize_t readn(int fd, void* buf, size_t count);
ssize_t writen(int fd, const void* buf, size_t count);
ssize_t readline(int fd, void* buf, size_t count);

int main(int argc, char* argv[]){
	int fd;
	fd=open("test.txt", O_CREAT|O_RDWR, S_IRWXU|S_IRUSR);
	assert(fd!=-1);
	
	char buf[15]="hello world";
	ssize_t ret;

	ret=writen(fd,buf,strlen(buf));
	assert(ret!=-1);

	off_t offset;
	offset=lseek(fd,0,SEEK_SET);
	assert(offset!=-1&&offset==0);

	char bufp[1024];
	ret=read(fd,bufp,sizeof(bufp));
	assert(ret!=-1);
	*(bufp+ret)='\0';//read不会自动添加'\0'，如果不添加会导致最后一位乱码
	fputs(bufp,stdout);

	offset=lseek(fd,0,SEEK_SET);
	assert(offset!=-1&&offset==0);
	
	char bufq[1024];
	ret=readline(fd,bufq,sizeof(bufq));
	assert(ret!=-1);
	*(bufq+ret)='\0';
	fputs(bufq,stdout);

	close(fd);
	return 0;
}

ssize_t readn(int fd, void* buf, size_t count){
	size_t nleft=count;
	char* bufp=(char*)buf;
	ssize_t nread;
	while(nleft>0){
		if((nread=read(fd,bufp,nleft))<0){
			if(errno==EINTR){
				nread=0;
			}else{
				return -1;
			}
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
	char* bufp=(char*)buf;
	ssize_t nwrite;

	while(nleft>0){
		if((nwrite=write(fd,buf,nleft))<0){
			if(errno==EINTR){
				nwrite=0;
			}else{
				return -1;
			}
		}
		if(nwrite==0){
			break;
		}
		bufp+=nwrite;
		nleft-=nwrite;
	}
	return count-nleft;
}

ssize_t readline(int fd, void* buf, size_t count){
	size_t nleft=count;
	char* bufp=(char*)buf;
	char ch=0;
	ssize_t nreadline;

	while(nleft>0){
		if((nreadline=read(fd,&ch,1))<0){
			if(errno==EINTR){
				nreadline=0;
			}else{
				return -1;
			}
		}

		assert(nreadline==1);
		*bufp++=ch;
		nleft-=nreadline;

		if(ch=='\n'||nreadline==0){
			break;
		}

	}

	return count-nleft;
}

/*
 * 对于write和read函数而言，务必注意指针位置偏移量，因为它们都会改变指针位置
 * read读出的字符在末尾并不会添加结束符，因此需要手动添加'\0';
 */
