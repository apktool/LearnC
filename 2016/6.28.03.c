//fcntl()文件控制操作
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>

#define OpenWay O_RDWR|O_CREAT|O_EXCL
#define AttiWay S_IRUSR|S_IWUSR

int main(int argc, char* argv[]){
	int fd;

	fd=open("123.txt",OpenWay,AttiWay);
	if(fd==-1){
		printf("Open Failed\n");
	}

	int flag;
	flag=fcntl(fd,F_GETFL);
	printf("fd:%d\tflag:%d\n",fd,flag);

	int newfd;
	newfd=dup(fd);
	printf("newfd:%d\n",newfd);

	flag=dup2(fd,newfd);
	printf("newfd:%d\tflag:%d\n",newfd,flag);
	
	if(close(fd)==-1){
		printf("Close Failed\n");
	}
	return 0;
}
