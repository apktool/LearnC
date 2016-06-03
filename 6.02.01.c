#include<stdio.h>

int main(int argc,char* argv[]){
	//使用位操作实现奇偶判断
	int m=4;
	if(m&0x01){
		printf("Odd\n");
	}else{
		printf("Even\n");
	}

	//使用位移操作实现乘2和除2的计算
	int n=8,k;
	k=n>>1;
	printf("Division:%d\n",k);

	k=n<<1;
	printf("Times:%d\n",k);
	return 0;
}
