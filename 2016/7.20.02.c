/**
 * @file 7.20.02.c
 * @brief TRACE_LOG()|自定义输出函数以及格式
 * @author LiWenGang
 * @date 2016-07-20
 */
#include<stdarg.h>
#include<stdio.h>

#define TRACE_LOG(x)\
	{\
		loglocal(__FILE__,__LINE__,__FUNCTION__);\
		logMessage x;\
	}

static void loglocal(const char* filename,const int linenum, const char* function);
static void logMessage(const char* format,...);

int main(int argc, char* argv[]){
	char ch[10]="hello";
	char oo[3]="!!";
	TRACE_LOG(("hello world !!\n"));
	TRACE_LOG(("%s world !!\n",ch));
	TRACE_LOG(("%s world %s\n",ch,oo));
	return 0;
}

static void loglocal(const char* filename,const int linenum, const char* function){
	printf("%s|%d|%s|INFO: ",filename,linenum,function);
}

static void logMessage(const char* format,...){
	va_list argList;
	va_start(argList,format);
	vprintf(format,argList);
	va_end(argList);
}
