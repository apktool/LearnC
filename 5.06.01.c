#include<stdio.h>
#include<stdlib.h>

typedef char ElemType;
typedef struct BiTNode{
	struct BiTNode *child[2];
	ElemType data;
}BiTNode, *BiTree;

BiTree CreatBiTree(BiTNode*);
void PreOrder(BiTNode*);

int main(int argc,char* argv[]){
	BiTNode *T=(BiTNode*)malloc(sizeof(BiTNode));
	T=CreatBiTree(T);
	PreOrder(T);
	printf("\n");
	return 0;
}

BiTree CreatBiTree(BiTNode* T){
	ElemType x;
	scanf("%c",&x);
	if(x==35){
		return T;
	}
	T=(BiTNode*)malloc(sizeof(BiTNode));
	T->data=x;
	T->child[0]=CreatBiTree(T->child[0]);
	T->child[1]=CreatBiTree(T->child[1]);
	return T;
}

void PreOrder(BiTNode* T){
	if(T==NULL){
		return;
	}
	printf("%c",T->data);
	PreOrder(T->child[0]);
	PreOrder(T->child[1]);
}
