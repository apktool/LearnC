#include<stdio.h>
#include<stdlib.h>
#define MaxSize 20

typedef int ElemType;
typedef struct BiTNode{
	ElemType data;
	struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;

BiTNode* BST_Create(BiTNode*,ElemType*);
int BST_Insert(BiTNode**,ElemType);
int BST_Search(BiTNode*,ElemType);
int BST_Delete(BiTNode*,ElemType);

void BST_Judge(BiTNode*);
void PreOrder(BiTNode*);
void InOrder(BiTNode*);

int main(int argc, char* argv[]){
	ElemType ch[MaxSize]={
		9,5,13,3,7,11,15,4,6,10,16,-1
	};

	BiTNode* T=NULL;
	T=BST_Create(T,ch);
	
	BST_Judge(T);

	int flag;
	ElemType num;
	printf("Please input the number you will insert: ");
	scanf("%d",&num);

	flag=BST_Insert(&T,num);
	flag?printf("Illeged Insert\n"):printf("Insert Success\n");

	printf("Please input the number you will Find: ");
	scanf("%d",&num);
	flag=BST_Search(T,num);
	flag?printf("Not Found\n"):printf("Find the number: %d\n",num);

	printf("Please input the number you will Delete: ");
	scanf("%d",&num);
	flag=BST_Delete(T,num);
	flag?printf("illege Delete\n"):printf("Delete Success\n");

	BST_Judge(T);
	return 0;
}

BiTree BST_Create(BiTNode* T, ElemType ch[]){
	int flag,i=0;
	while(ch[i]!=-1){
		flag=BST_Insert(&T,ch[i++]);
		if(flag){
			printf("Illeged Insert\n");
		}
	}
	return T;
}

int BST_Insert(BiTNode** T,ElemType ch){
	if((*T)==NULL){
		(*T)=(BiTNode*)malloc(sizeof(BiTNode));
		(*T)->data=ch;
		(*T)->lchild=NULL;
		(*T)->rchild=NULL;
		return 0;
	}
	if(ch<(*T)->data){
		return BST_Insert(&(*T)->lchild,ch);
	}else if(ch>(*T)->data){
		return BST_Insert(&(*T)->rchild,ch);
	}else{
		return -1;
	}
}

int BST_Search(BiTNode* T,ElemType ch){
	if(T==NULL){
		return -1;
	}
	if(ch<T->data){
		return BST_Search(T->lchild,ch);
	}else if(ch>T->data){
		return BST_Search(T->rchild,ch);
	}else{
		return 0;
	}
}

int BST_Delete(BiTNode* T,ElemType ch){
	BiTNode *pre=T;
	BiTNode *p=T;
	while(p!=NULL){
		if(ch<p->data){
			pre=p;
			p=p->lchild;
		}else if(ch>p->data){
			pre=p;
			p=p->rchild;
		}else{
			break;
		}
	}
	if(p==NULL){
		return -1;
	}

	if(p->lchild==NULL&&p->rchild==NULL){
		if(p->data<pre->data){
			pre->lchild=NULL;
		}else{
			pre->rchild=NULL;
		}	
		free(p);
	}

	if(p->lchild!=NULL&&p->rchild==NULL){
		if(p->data<pre->data){
			pre->lchild=p->lchild;
		}else{
			pre->rchild=p->lchild;
		}
		free(p);
	}

	if(p->lchild==NULL&&p->rchild!=NULL){
		if(p->data<pre->data){
			pre->lchild=p->rchild;
		}else{
			pre->rchild=p->rchild;
		}
		free(p);
	}

	if(p->lchild!=NULL&&p->rchild!=NULL){
		BiTNode *r=p;
		p=p->rchild;
		while(p->lchild!=NULL){
			pre=p;
			p=p->lchild;
		}
		r->data=p->data;
		if(p->data<pre->data){
			pre->lchild=p->rchild;
		}else{
			pre->rchild=p->rchild;
		}
		free(p);
	}
	return 0;
}

void BST_Judge(BiTNode* T){
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
