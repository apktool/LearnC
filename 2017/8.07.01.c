/**
 * @Synopsis  typedef unsigned int type[4]
 *
 * @Param argc
 * @Param argv[]
 *
 * @Returns   
 */
#include<stdio.h>

int main(int argc, char* argv[]){
	unsigned int *p;

	typedef unsigned int type[4];
	type gdt={1, 2, 3, 4};

	p=gdt;
	printf("%u\n", *p);
	printf("%u\n", *(p+1));
	printf("%u\n", *(p+2));
	printf("%u\n", *(p+3));

	printf("-----------------------\n");
	
	unsigned int gpt[4]={1, 2, 3, 4};

	p=gpt;
	printf("%u\n", *p);
	printf("%u\n", *(p+1));
	printf("%u\n", *(p+2));
	printf("%u\n", *(p+3));
	
	return 0;
}

/*
 * typedef unsigned int type[4];
 * type gdt={1, 2, 3, 4};
 *
 * 上面两句从使用效果上等价于
 *
 * unsigned int gpt[4]={1, 2, 3, 4};
 * 
 */
