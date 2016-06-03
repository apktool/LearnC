#include<stdio.h>
#define MAX_MSG_LEN 32

int main(int argc,char* argv[]){
	char appid[MAX_MSG_LEN];
	int arry[MAX_MSG_LEN];
	int lenc=sizeof(appid);
	int leni=sizeof(arry);
	printf("%d\n",lenc);
	printf("%d\n",leni);
}
