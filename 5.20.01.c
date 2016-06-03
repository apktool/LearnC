#include<stdio.h>

//#define MAX(a,b) ((a)>(b)?(a):(b))
#define MAX(a,b) (a>b?a:b)

int a[]={
	0,9,5,3,4,1,8,2,7,6
};

int max(int);

int main(int argc,char* argv[]){
	int ab=max(9);
	printf("%d\n",ab);
	return 0;
}

int max(int n){
	return n==0?a[0]:MAX(a[n],max(n-1));
}
