#include<stdio.h>
#include<string.h>
#define N 6

//strncmp比较的A的前面size个字符，切记不可比较指定字符，比如strncmp(A[1],"1",1);这是错误的

int main(int argc,char* argv[]){
	char A[N+1]="089001";
	//strncmp比较的是指针A到A+size之间的字符。
	if(strncmp(A+1,"8",1)==0){
		printf("Success!\n");
	}else{
		printf("Fail\n");
	}

	char *B="029001";
	if(strncmp(B+1,"2",1)==0){
		printf("Success\n");
	}else{
		printf("Fail\n");
	}
	
//双引号括起来的一般表示是一个字符串，C风格的字符串后米娜有一个'\0'
//单引号括起来的是一个字符，一共就一个字节。
//
	char a='a';
	char b[N]="a";

	printf("%c\n",'a');
	printf("%s\n","b");
	return 0;

}
