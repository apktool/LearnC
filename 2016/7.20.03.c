/**
 * @file 7.20.03.c
 * @brief fopen(),fgets(),fclose()
 * @author LiWenGang
 * @date 2016-07-20
 */
#include<stdio.h>
#define MaxSize 512

int main(int argc, char* argv[]){
	FILE *fp;
	fp=fopen("123.txt","r");
	if(fp==NULL){
		perror("error fopen");
	}

	char buf[MaxSize];
	fgets(buf,sizeof(buf),fp);
	printf("%s",buf);
	fgets(buf,sizeof(buf),fp);
	printf("%s",buf);

	int flag;
	flag=fclose(fp);
	if(flag==-1){
		perror("error fclose");
	}
	return 0;
}
