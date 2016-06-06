//二叉排序树Binary Search Tree[BST]
#include<stdio.h>
#include<stdlib.h>
#define MaxSize 10
typedef int ElemType;
typedef struct BiTNode{
	ElemType data;
	struct BiTNode *lchild, *rchild;
}BiTNode,*BiTree;

BiTNode* CreateBiTree(BiTNode*,ElemType*);
void BST_Insert(BiTNode**,ElemType);
void BST_Search(BiTNode*,ElemType);

void PreOrder(BiTNode*);
void InOrder(BiTNode*);

int main(int argc,char* argv[]){
	ElemType ch[MaxSize]={
		4,2,5,1,3,6,-1
	};

	BiTNode* T=NULL;
	T=CreateBiTree(T,ch);
	PreOrder(T);
	printf("\n");
	InOrder(T);
	printf("\n");

	printf("%s|%d Complete\n",__FUNCTION__,__LINE__);

	return 0;
}

BiTNode* CreateBiTree(BiTNode* T,ElemType ch[]){
	for(int i=0;i<MaxSize&&ch[i]!=-1;i++){
		BST_Insert(&T,ch[i]);
	}
	return T;
}

void BST_Insert(BiTNode** T,ElemType ch){
	if(*T==NULL){
		*T=(BiTNode*)malloc(sizeof(BiTNode));
		(*T)->data=ch;
		(*T)->lchild=NULL;
		(*T)->rchild=NULL;
	}
	if(ch<(*T)->data){
		BST_Insert(&(*T)->lchild,ch);
	}
	if(ch>(*T)->data){
		BST_Insert(&(*T)->rchild,ch);
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
