#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(int argc, char* argv[]){

	char A[]="009001";
	char *B="009001";
	char C[]={'0','0','9','0','0','1'};

	printf("%ld\n",sizeof(A));
	printf("%ld\n",sizeof(B));
	printf("%ld\n",sizeof(C));
	printf("%ld\n",strlen(A));
	return 0;
}
