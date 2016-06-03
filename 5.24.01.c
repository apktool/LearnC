#include<stdio.h>

void swap1(int*, int*);
void swap2(int*, int*);

int main(int argc, char* argv[]){
	int m=3,n=4;
	printf("%d,%d\n",m,n);
	swap1(&m,&n);
	printf("%d,%d\n",m,n);
	swap2(&m,&n);
	printf("%d,%d\n",m,n);
	return 0;
}

void swap1(int* a, int* b){
	int temp;
	temp=*a;
	*a=*b;
	*b=temp;
}

void swap2(int* a, int* b){
	*a=*a^*b;
	*b=*a^*b;
	*a=*a^*b;
}
