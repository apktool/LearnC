//雷神之锤3，sqrt函数的实现
//http://www.cnblogs.com/pkuoliver/archive/2010/10/06/1844725.html
#include<stdio.h>

#define EPS 0.001

float Sqrt(float);

int main(int argc, char* argv[]){
	float m,n;
	scanf("%f",&n);
	m=Sqrt(n);
	printf("%f\n",m);
	return 0;
}

float Sqrt(float n){
	float xhalf=0.5f*n;
	printf("%f\n",xhalf);
	int i=*(int*)&n;
	printf("%d\n",i);

	i=0x5f375a86-(i>>1);
	n=*(float*)&i;
	n=n*(1.5f-xhalf*n*n);
	n=n*(1.5f-xhalf*n*n);
	n=n*(1.5f-xhalf*n*n);

	return 1/n;
}
