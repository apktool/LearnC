#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXLEN 512

typedef void SESS;

typedef struct _PACK{
	int len;//一个域的长度
	char type[MAXLEN];//描述该域的类型为二进制还是字符型还是整型
	char keyname[MAXLEN];//域描述
	char RejCode[MAXLEN];//拒绝码
}Area;


int decode_DEMO(char*,SESS*);
int main(int argc,char* argv[]){
	char msg[24+1]="01234567";
	SESS *sess;
	int flag=decode_DEMO(msg,sess);
	return 0;
}

int decode_DEMO(char* msg,SESS* sess){
	Area pack[MAXLEN];

	char bitmap[24+1];
	int FiedNum=0;
	memcpy(bitmap,msg,24);
	if(bitmap[0]&0x80){
		printf("Have 2th bitmap");
		if(bitmap[8]&0x80){
			printf("Have 3th bitmap");
			FiedNum=192;
		}else{
			FiedNum=128;
		}
	}else{
		FiedNum=64;
	}

	//打印位图中值为1在域中所对应的序号
	int i;
	for(i=1;i<FiedNum;i++){
		if(bitmap[(i-1)/8]&(0x80>>(i-1)%8)){
			printf("%4d",i);
		}
	}

	for(i=2;i<=FiedNum;i++){
		
	}

}
