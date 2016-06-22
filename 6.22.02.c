//liunx系统编程，open().read(),write(),close()
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>

#define MaxSize 512

int main(int argc, char* argv[]){
	int fd;

	fd=open("myfirst",O_RDWR|O_CREAT,S_IRUSR|S_IWUSR);
	if(fd==-1){
		printf("Open Failed!\n");
	}
	char buffer[MaxSize]="Hello Latex";
	ssize_t numMax;

	numMax=write(fd,buffer,MaxSize);
	numMax==-1?printf("Write Failed\n"):printf("Write Success\n");

	numMax=read(fd,buffer,MaxSize);
	printf("numMax:%ld\n",numMax);
	buffer[numMax]=0;
	numMax==-1?printf("Read Failed\n"):printf("Read Success|%s\n",buffer);

	if(close(fd)==-1){
		printf("Close Failed\n");
	}
	return 0;
}

