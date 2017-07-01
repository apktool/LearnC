/**
 * @file 7.20.01.c
 * @brief vprintf|变参函数
 * @author LiWenGang
 * @date 2016-07-20
 */
#include<stdarg.h>
#include<stdio.h>

static void logMessage(const char* format,...);

int main(int argc,char* argv[]){
	logMessage("hello wolrd\n");
	logMessage("hello latex %d\n",2016);
	return 0;
}

static void logMessage(const char* format,...){
	va_list argList;
	va_start(argList,format);
	vprintf(format,argList);
	va_end(argList);
}
