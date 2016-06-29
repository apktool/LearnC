//getenv(),
#include<stdio.h>
#include<stdlib.h>

int main(int argc,char* argv[]){
	char *env;
	env=getenv("PATH");
	printf("%s\n",env);
	return 0;
}
