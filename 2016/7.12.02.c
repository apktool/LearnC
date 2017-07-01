/**
 * @file 7.12.02.c
 * @brief getrlimit(),setrlimit()|进程资源限制
 * @author LiWenGang
 * @date 2016-07-12
 */
#include<sys/resource.h>
#include<stdio.h>
#include<stdlib.h>

void PrintRlimit(int);

int main(int argc, char* argv[]){
	printf("Initial maximum process limits:\t");
	PrintRlimit(RLIMIT_NPROC);

	struct rlimit rl;
	rl.rlim_cur=30;
	rl.rlim_max=100;
	int flag=setrlimit(RLIMIT_NPROC,&rl);
	if(flag==-1){
		perror("setrlimit");
	}

	printf("New maximum process limits:\t");
	PrintRlimit(RLIMIT_NPROC);
	return 0;
}

void PrintRlimit(int resource){
	struct rlimit rlim;

	int flag=getrlimit(resource,&rlim);
	if(flag==-1){
		perror("error getrlimit");
	}

	if(rlim.rlim_cur==RLIM_INFINITY){
		printf("infinite\n");
	}else{
		printf("%ld\t",rlim.rlim_cur);
	}

	if(rlim.rlim_max==RLIM_INFINITY){
		printf("infinite\n");
	}else{
		printf("%ld\t\n",rlim.rlim_max);
	}
}
