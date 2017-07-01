#include<stdio.h>
#include<stdlib.h>
#define N 5

int main(int argc, char* argv[]){
	char ch[N+1]={"02345"};
	puts(ch);
	printf("%d\n",atoi(ch));
	printf("%ld\n",atol(ch));

	char hc[N+1]={" 1234"};
	puts(hc);
	printf("%d\n",atoi(hc));

	return 0;
}
