/**
 * @file 7.20.04.c
 * @brief 回调函数的另类用法
 * @author LiWenGang
 * @date 2016-07-20
 */
#include<stdio.h>

typedef void(*fun)(void);
typedef struct build{
	char* name;
	fun handler;
}build;

void do_exit(void);
void do_about(void);

int main(int argc, char* argv[]){
	build ch[]={
		{"exit",do_exit},
		{"about",do_about}
	};
	printf("%s\n",ch[0].name); ch[0].handler();
	printf("%s\n",ch[1].name); ch[1].handler();
	return 0;
}

void do_exit(void){
	printf("what's the fuck exiting..\n");
}

void do_about(void){
	printf("copyright @2016-7-20\n");
}
