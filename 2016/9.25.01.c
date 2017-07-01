/**
 * @file 9.25.01.c
 * @brief 异常处理jmp
 * @author LiWenGang
 * @date 2016-09-25
 */
#include<stdio.h>
#include<setjmp.h>

jmp_buf buf;

double Divide(double a, double b){
	if(b==0.0){
		longjmp(buf,1);
	}else{
		return a/b;
	}
}


int main(int argc, char* argv[]){
	int ret=setjmp(buf);
	if(ret==0){
		printf("%f\n",Divide(5.0,0.0));
	}
	if(ret==1){
		printf("Division by zero\n");
	}
	return 0;
}
