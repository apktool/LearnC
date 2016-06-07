//平衡二叉树|Balanced Binary Tree[AVL]
#include<stdio.h>
#include<stdlib.h>

#define MaxSize 20
typedef int ElemType;
typedef struct BiTNode{
	ElemType data;
	struct BiTNode *lchild,*rchild;
	int height;
}BiTNode, BiTree;

BiTNode* AVL_Create(BiTNode*,ElemType*);
int AVL_Insert(BiTNode**,ElemType);
int AVL_Search(BiTNode*,ElemType);
int AVL_Delete(BiTNode*,ElemType);

void AVL_Judge(BiTNode*);
void PreOrder(BiTNode*);
void InOrder(BiTNode*);

int Max(int,int);
int Height(BiTNode*);

void RotateLeftLeft(BiTNode*);
void RotateLeftRight(BiTNode*);
void RotateRightRight(BiTNode*);
void RotateRightLeft(BiTNode*);

int main(int argc,char* argv[]){
	BiTNode* T=NULL;
	ElemType ch[MaxSize]={
		6,3,7,1,4,2,-1
	};
	T=AVL_Create(T,ch);

	AVL_Judge(T);

/*
	int flag;
	ElemType num;

	printf("Please input the number you will insert: ");
	scanf("%d",&num);
	flag=AVL_Insert(&T,num);
	flag?printf("illegal Insert\n"):printf("Insert Success\n");

	printf("Please input the number you want to find: ");
	scanf("%d",&num);
	flag=AVL_Search(T,num);
	flag?printf("Not Find\n"):printf("Find it\n");

	printf("Please input the number you want to delete: ");
	scanf("%d",&num);
	flag=AVL_Delete(T,num);
	flag?printf("Delete Failed\n"):printf("Delete Success\n");

	AVL_Judge(T);
*/
	return 0;
}

BiTNode* AVL_Create(BiTNode* T,ElemType ch[]){
	int flag,i=0;
	while(ch[i]!=-1){
		flag=AVL_Insert(&T,ch[i++]);
		if(flag){
			printf("Insert illegal\n");
			break;
		}
	}
	return T;
}

int AVL_Insert(BiTNode** T,ElemType ch){
	if((*T)==NULL){
		(*T)=(BiTNode*)malloc(sizeof(BiTNode));
		(*T)->data=ch;
		(*T)->lchild=NULL;
		(*T)->rchild=NULL;
		(*T)->height=Max(Height((*T)->lchild),Height((*T)->rchild))+1;	
		return 0;
	}
	if(ch<(*T)->data){
		return AVL_Insert(&(*T)->lchild,ch);
		if(Height((*T)->lchild)-Height((*T)->rchild)==2){
			if(ch<(*T)->lchild->data){
				RotateLeftLeft(*T);
			}else{
				RotateLeftRight(*T);
			}
		}
	}else if(ch>(*T)->data){
		return AVL_Insert(&(*T)->rchild,ch);
		if(Height((*T)->lchild)-Height((*T)->rchild)==2){
			if(ch<(*T)->rchild->data){
				RotateRightRight(*T);
			}else{
				RotateRightLeft(*T);
			}
		}

	}else{
		return -1;
	}
}

void RotateLeftLeft(BiTNode* T){
	BiTNode *p=T;
	BiTNode *q=p->lchild;

	q=p->lchild;
	p->lchild=q->rchild;
	q->rchild=p;

	p->height=Max(Height(p->lchild),Height(p->rchild))+1;
	q->height=Max(Height(q->lchild),p->height)+1;
}

void RotateLeftRight(BiTNode* T){
	BiTNode *p=T;
	BiTNode *q=p->lchild;
	RotateRightRight(q);
	RotateLeftLeft(p);
}

void RotateRightRight(BiTNode* T){
	BiTNode *p=T;
	BiTNode *q=p->rchild;

	p->rchild=q->lchild;
	q->lchild=p;

	p->height=Max(Height(p->lchild),Height(p->rchild))+1;
	q->height=Max(Height(q->rchild),p->height)+1;
}

void RotateRightLeft(BiTNode* T){
	BiTNode *p=T;
	BiTNode *q=p->rchild;
	
	RotateLeftLeft(q);
	RotateRightRight(p);
}

int Max(int a,int b){
	return a>b?a:b;
}

int Height(BiTNode* T){
	return T?T->height:-1;
}

void AVL_Judge(BiTNode* T){
	PreOrder(T);printf("\n");
	InOrder(T);printf("\n");
}

void PreOrder(BiTNode* T){
	if(T==NULL){
		return;
	}
	printf("%3d|%d",T->data,T->height);
	PreOrder(T->lchild);
	PreOrder(T->rchild);
}

void InOrder(BiTNode* T){
	if(T==NULL){
		return;
	}
	InOrder(T->lchild);
	printf("%3d|%d",T->data,T->height);
	InOrder(T->rchild);
}
