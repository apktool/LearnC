//Complete copy function about between string A and string B

#include<stdio.h>
#include<string.h>
#define N 5

int main(int argc, char* argv[]){
	char B[N+1]={"Hello"};
	char A[N+1];
	memcpy(A,B,sizeof(B));
	puts(A);
	memset(A,0,sizeof(A));
	
	snprintf(A,sizeof(A),B,sizeof(B));
	puts(A);
	memset(A,0,sizeof(A));

	strncpy(A,B,sizeof(B));
	puts(A);
	memset(A,0,sizeof(A));
	return 0;
}
