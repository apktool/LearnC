//bool的实现方式
//C99中引入布尔类型，并且定义新的关键字_Bool，同时新添加<stdbool.h>头文件
#include<stdio.h>
//#include<stdbool.h>

#define bool _Bool
#define true 1
#define false 0

int main(int argc,char* argv[]){
	bool flag;
	flag=true;
	printf("bool:%d|%d|%d\n",true,false,flag);
	return 0;
}
