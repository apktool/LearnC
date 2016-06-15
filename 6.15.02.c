#include<stdio.h>
#include<stdlib.h>
typedef int Elemtype;
typedef struct LNode{
	Elemtype data;
	struct LNode *next;
}LNode,*LinkList;
int main(int argc,char* argv[]){
	LNode *p;
	p=(LNode*)malloc(sizeof(LNode));
	p?printf("NOT NULL|%p\n",p):printf("NULL\n");
	return 0;
}
