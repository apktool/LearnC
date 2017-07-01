//浮点数的二进制表示
//http://www.ruanyifeng.com/blog/2010/06/ieee_floating-point_representation.html

#include<stdio.h>

int main(int argc, char* argv[]){
	int num=9;
	float *pFloat=&num;

	printf("num: %d\n",num);
	printf("*pFloat: %f\n",*pFloat);

	*pFloat=9.0;

	printf("num: %d\n",num);
	printf("*pFloat: %f\n",*pFloat);
	
	return 0;
}
