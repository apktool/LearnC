/**
 * @file 6.30.01.c
 * @brief fork(),getpid()
 * @author LiWenGang
 * @date 2016-06-30
 */
#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>

int main(int argc,char* argv[]){
	pid_t childPID;
	int val=1;
	int cnt=4;
	childPID=fork();
	switch(childPID){
		case -1:printf("fork error");break;
		case 0:val+=2;cnt/=2;break;
		default:sleep(2);break;
	}
	printf("%d\t%d\t%s\tval=%d\tcnt=%d\n",childPID,getpid(),childPID==0?"childe":"parent",val,cnt);
	return 0;
}
