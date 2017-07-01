//使用二分法求解开方
#include<stdio.h>
#include<math.h>
#define EPS 0.0001 //精度控制

float Sqrt(float);

int main(int argc,char* argv[]){
	float m,n;
	scanf("%f",&n);
	m=Sqrt(n);
	printf("%f\n",m);
	return 0;
}

float Sqrt(float n){
	float low=0,high=n;
	float mid=(low+high)/2;
	float last;
	if(n<0){
		return n;
	}
	while(fabs(mid-last)>EPS){
		if(mid*mid<n){
			low=mid;
		}else{
			high=mid;
		}
		last=mid;
		mid=(low+high)/2;
	}
	return mid;
}
