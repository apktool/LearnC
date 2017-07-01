#include<stdio.h>
#include<string.h>
#define N 5

int main(int argc,char* argv[]){
	char A[N*3]={"Hello world"};
	char B[2];
	strncpy(B,A,sizeof(B));
	printf("%s\n",A);
	printf("%s\n",B);
	char *ptr=B;
	for(;*ptr!='\0';ptr++){
		printf("%c\n",*ptr);
	}
}

