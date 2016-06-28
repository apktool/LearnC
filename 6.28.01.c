//open(),read(),lseek(),close()
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>

#define OpenWay O_RDWR|O_APPEND|O_CREAT
#define AttiWay S_IRUSR|S_IWUSR
#define MaxLen 15

int main(int argc, char* argv[]){
	int fd;
	fd=open("123.txt",OpenWay,AttiWay);
	if(fd==-1){
		printf("Open the file Successly\n");
	}
	
	ssize_t numMax;
	char buf[MaxLen];
	off_t pos;
	pos=lseek(fd,3,SEEK_SET);
	numMax=read(fd,buf,MaxLen);
	buf[numMax]=0;
	printf("%ld->%ld->%s\n",pos,numMax,buf);

	if(close(fd)==-1){
		printf("Close File Failed\n");
	}
	return 0;
}
