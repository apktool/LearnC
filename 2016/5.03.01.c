#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 16

int main(int argc,char* argv[])
{
	char A[N]={"Hello Word"};
	char* str1=(char*)malloc(sizeof(char));
	snprintf(str1, sizeof(A), "%s",A);
	puts(str1);
	free(str1);

	char B[N]={"Hello Latex"};
	char* str2=(char*)malloc(sizeof(char));
	strncpy(str2,B,sizeof(B));
	puts(str2);
	free(str2);
	
	return 0;
}
