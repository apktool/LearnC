//伸展树|Splay Tree[ST]
#include<stdio.h>
#include<stdlib.h>

#define MaxSize 20

typedef int ElemType;
typedef struct BiTNode{
	ElemType data;
	struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;

BiTNode* ST_Create(BiTNode*,ElemType*);
BiTNode* ST_Insert(BiTNode*,ElemType);
BiTNode* ST_Splay(BiTNode*,ElemType);
BiTNode* ST_Search(BiTNode*,ElemType);
BiTNode* ST_Delete(BiTNode*,ElemType);

BiTNode* ST_MaxNum(BiTNode*);
BiTNode* ST_MinNum(BiTNode*);

BiTNode* RotateLeft(BiTNode*);
BiTNode* RotateRight(BiTNode*);

void ST_Judge(BiTNode*);
void PreOrder(BiTNode*);
void InOrder(BiTNode*);

int main(int argc, char* argv[]){
	ElemType ch[MaxSize]={
		4,2,6,1,3,5,7,8,-1
	};

	BiTNode* P=NULL;
	BiTNode* T=NULL;
	T=ST_Create(T,ch);

	ST_Judge(T);

	ElemType num;
	printf("Please input the number you will insert: ");
	scanf("%d",&num);
	P=ST_Insert(T,num);
	P?printf("The number is inserted successlly\n"):printf("Insert Failed");
	if(P!=NULL){
		T=ST_Splay(T,num);
		T?printf("The tree is Spalyed successlly\n"):printf("Splay Failed");
	}

	printf("Please input the number you will find: ");
	scanf("%d",&num);
	T=ST_Splay(T,num);
	T?(T->data==num?printf("Find %d\n",T->data):printf("Not Find\n")):printf("Not Find\n");

	P=ST_MaxNum(T);
	P?printf("The Max number is %d\n",P->data):printf("Not Find\n");

	P=ST_MinNum(T);
	P?printf("The Min number is %d\n",P->data):printf("Not Find\n");

	ST_Judge(T);
	return 0;
}

BiTNode* ST_Create(BiTNode* T, ElemType ch[]){
	int i=0,tmp;
	while(ch[i]!=-1){
		tmp=ch[i++];
		T=ST_Insert(T,tmp);
		if(T==NULL){
			printf("Illege created\n");
			break;
		}
		T=ST_Splay(T,tmp);
	}
	return T;
}

BiTNode* ST_Insert(BiTNode* T, ElemType ch){
	if(T==NULL){
		T=(BiTNode*)malloc(sizeof(BiTNode));
		T->data=ch;
		T->lchild=NULL;
		T->rchild=NULL;
	}

	if(ch<T->data){
		T->lchild=ST_Insert(T->lchild,ch);
	}
	if(ch>T->data){
		T->rchild=ST_Insert(T->rchild,ch);
	}

	return T;
}

BiTNode* ST_Splay(BiTNode* T, ElemType ch){
	BiTNode *L, *R, N;
	L=&N;R=&N;
	N.lchild=NULL;N.rchild=NULL;

	if(T==NULL){
		return NULL;
	}

	while(1){
		if(ch<T->data){
			if(T->lchild==NULL){
				break;
			}
			if(ch<T->lchild->data){
				T=RotateLeft(T);
				if(T->lchild==NULL){
					break;
				}
			}
			R->lchild=T;
			R=T;
			T=T->lchild;
		}else if(ch>T->data){
			if(T->rchild==NULL){
				break;
			}
			if(ch>T->rchild->data){
				T=RotateRight(T);
				if(T->rchild==NULL){
					break;
				}
			}
			L->rchild=T;
			L=T;
			T=T->rchild;
		}else{
			break;
		}
	}
	L->rchild=T->lchild;
	R->lchild=T->rchild;
	T->lchild=N.rchild;
	T->rchild=N.lchild;

	return T;
}

BiTNode* ST_Search(BiTNode*T ,ElemType ch){
	T=ST_Splay(T,ch);
	return T;
}

BiTNode* ST_MaxNum(BiTNode* T){
	if(T==NULL){
		return NULL;
	}
	while(T->rchild){
		T=T->rchild;
	}
	return T;
}

BiTNode* ST_MinNum(BiTNode* T){
	if(T==NULL){
		return NULL;
	}
	while(T->lchild){
		T=T->lchild;
	}
	return T;
}

BiTNode* RotateLeft(BiTNode* T){
	BiTNode* p=T;
	BiTNode* q=p->lchild;

	p->lchild=q->rchild;
	q->rchild=p;

	return q;
}

BiTNode* RotateRight(BiTNode* T){
	BiTNode* p=T;
	BiTNode* q=p->rchild;

	p->rchild=q->lchild;
	q->lchild=p;

	return q;
}

void ST_Judge(BiTNode* T){
	PreOrder(T);printf("\n");
	InOrder(T);printf("\n");
}

void PreOrder(BiTNode* T){
	if(T==NULL){
		return;
	}
	printf("%3d",T->data);
	PreOrder(T->lchild);
	PreOrder(T->rchild);
}

void InOrder(BiTNode* T){
	if(T==NULL){
		return;
	}
	InOrder(T->lchild);
	printf("%3d",T->data);
	InOrder(T->rchild);
}
