/**
 * @file 10.30.03.c
 * @brief 网络套接字|gethostbyname()
 * @author LiWenGang
 * @date 2016-10-30
 */
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<unistd.h>
#include<errno.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define h_addr h_addr_list[0]

#define ERR_EXIT(m) \
	do{ \
		perror(m); \
		exit(EXIT_FAILURE); \
	}while(0)

extern int gethostname(char *name, size_t len);
int getloaclip(char * p);

int main(int argc, char* argv[]){
	char host[100]={0};
	if(gethostname(host,sizeof(host))<0){
		ERR_EXIT("gethostname");
	}

	struct hostent *hp;
	if((hp=gethostbyname(host))==NULL){
		ERR_EXIT("gethostbyname");
	}

	int i=0;
	while(hp->h_addr_list[i]!=NULL){
		printf("%s\n",inet_ntoa(*(struct in_addr*)hp->h_addr_list[i]));
		i++;
	}

	char ip[16]={0};
	getloaclip(ip);
	printf("localip=%s\n",ip);

	return 0;
}

int getloaclip(char * ip){//获取本机IP地址
	struct hostent* hp;
	char host[100]={0};
	if(gethostname(host,sizeof(host))<0){
		ERR_EXIT("gethostname");
	}
	if((hp=gethostbyname(host))==NULL){
		return -1;
	}
	strcpy(ip,inet_ntoa(*(struct in_addr*)hp->h_addr));//#define h_addr h_addr_list[0]
	return 0;
}
