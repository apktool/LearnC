//environ|打印环境变量
#include<stdio.h>

extern char **environ;

int main(int argc, char* argv[]){
	for(char**ep=environ;*ep!=NULL;ep++){
		puts(*ep);
	}
	return 0;
}
