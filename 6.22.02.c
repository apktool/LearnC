//liunx系统编程，open(),read(),write(),close()
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>

#define MaxSize 512

int main(int argc, char* argv[]){
	int fd;

	fd=open("123.txt",O_RDWR|O_CREAT,S_IRUSR|S_IWUSR);
	if(fd==-1){
		printf("Open Failed!\n");
	}
	char buffer[MaxSize]="Hello Latex";
	int len=strlen(buffer);

	ssize_t numMax;

	numMax=write(fd,buffer,len+1);
	numMax==-1?printf("Write Failed\n"):printf("Write Success|%ld\n",numMax);

	numMax=read(fd,buffer,MaxSize);
	//buffer[numMax]=0;
	//为什么返回的numMax值为0?
	numMax==-1?printf("Read Failed\n"):printf("Read Success|%ld->%s\n",numMax,buffer);

	if(close(fd)==-1){
		printf("Close Failed\n");
	}
	return 0;
}

