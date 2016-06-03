#include<stdio.h>
#include<string.h>

int main(int argc, char* argv[]){
	char str1[]="Hello World";
	char str2[]="lo";
	char* str=strstr(str1,str2);
	printf("%s",str);
	return 0;
}
