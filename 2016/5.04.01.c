#include<stdio.h>
#include<string.h>
#define N 5

int main(int argc,char* argv[]){
	char buff[N+1]={"11111"};
	puts(buff);
	memset(buff,0,sizeof(buff));
	puts(buff);

	int ch[N];
	memset(ch,50,sizeof(ch));
	for(int i=0;i<N;i++){
		printf("%x",ch[i]);
	}
	printf("\n");

	return 0;
}
