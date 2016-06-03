//使用牛顿迭代法求解开方
#include<stdio.h>
#include<math.h>
#define EPS 0.001

float Sqrt(float);

int main(int argc,char* argv[]){
	float m,n;
	scanf("%f",&n);
	m=Sqrt(n);
	printf("%f\n",m);
	return 0;
}

float Sqrt(float n){
	float val=n,last;
	while(fabs(val-last)>EPS){
		last=val;
		val=(val+n/val)/2;
	}
	return val;
}
