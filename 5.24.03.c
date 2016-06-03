//二叉排序树Binary Search Tree[BST]
#include<stdio.h>
#include<stdlib.h>

#define MaxSize 20
typedef int ElemType;
typedef struct BiTNode{
	ElemType data;
	struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

BiTree BST_Create(BiTNode*,ElemType*);
BiTNode* BST_Search(BiTNode*);
int BST_Insert(BiTNode**,ElemType);
void PreOrder(BiTNode*);
void InOrder(BiTNode*);

int main(int argc,char* argv[]){
	ElemType KeyName[MaxSize]={
		6,1,0,5,4,9,2,999
	};

	BiTNode* T=NULL;
	T=BST_Create(T,KeyName);

	PreOrder(T);
	printf("\n");
	InOrder(T);
	printf("\n");
	return 0;
}

BiTree BST_Create(BiTNode* T, ElemType ch[]){
	int flag,i=0;
	while(ch[i]!=999){
		flag=BST_Insert(&T,ch[i]);
		i++;
	}
	if(!flag){
		printf("Right\n");
	}else{
		printf("ERROR Repeat!\n");
	}
	
	return T;
}

int BST_Insert(BiTNode** T, ElemType k){
	if(*T==NULL){
		*T=(BiTNode*)malloc(sizeof(BiTNode));
		(*T)->data=k;
		(*T)->lchild=NULL;
		(*T)->rchild=NULL;
		return 0;
	}
	if(k==(*T)->data){
		return -1;
	}else if(k<(*T)->data){
		return BST_Insert(&(*T)->lchild, k);
	}else{
		return BST_Insert(&(*T)->rchild, k);
	}
}

void PreOrder(BiTNode* T){
	if(T==NULL){
		return;
	}
	printf("%d",T->data);
	PreOrder(T->lchild);
	PreOrder(T->rchild);
}

void InOrder(BiTNode* T){
	if(T==NULL){
		return;
	}
	InOrder(T->lchild);
	printf("%d",T->data);
	InOrder(T->rchild);
}
