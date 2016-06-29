//getenv(),setenv(),unsetenv()
#include<stdio.h>
#include<stdlib.h>

//setenv()和unsetenv()是<stdlib.h>提供的接口函数，但是不知为何需要显示声明，不然会有警告
int setenv(const char*,const char*,int);
int unsetenv(const char*);

int main(int argc, char* argv[]){
	char* env;
	env=getenv("PATH");
	printf("%s\n",env);

	int flag;
	flag=setenv("GREEK","Hello World",0);
	if(flag==-1){
		printf("Set environment Failed\n");
	}

	flag=unsetenv("GROOK");
	if(flag==-1){
		printf("Unset environment Failed\n");
	}

	env=getenv("GREEK");
	printf("\n%s\n",env);

	return 0;
}
