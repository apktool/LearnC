//二叉排序树|Binary Search Tree[BST]|递归插入，查找
#include<stdio.h>
#include<stdlib.h>
#define MaxSize 20

typedef int ElemType;
typedef struct BiTNode{
	ElemType data;
	struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;

BiTNode* BST_Create(BiTNode*,ElemType*);
BiTNode* BST_Insert(BiTNode*,ElemType);
BiTNode* BST_Search(BiTNode*,ElemType);
BiTNode* BST_Delete(BiTNode*,ElemType);

void BST_Judge(BiTNode*);
void PreOrder(BiTNode*);
void InOrder(BiTNode*);

int main(int argc, char* argv[]){
	ElemType ch[MaxSize]={
		9,5,13,3,7,11,15,4,6,10,16,-1
	};

	BiTNode* T=NULL;
	T=BST_Create(T,ch);

	BiTNode* P=T;
	BST_Judge(T);

	ElemType num;

	printf("Please input the number you will insert: ");
	scanf("%d",&num);
	P=BST_Insert(T,num);
	P?printf("Insert Success\n"):printf("Illeged Insert\n");

	printf("Please input the number you will Find: ");
	scanf("%d",&num);
	P=BST_Search(T,num);
	P?printf("Find the number: %d\n",num):printf("Not Found\n");

	printf("Please input the number you will Delete: ");
	scanf("%d",&num);
	P=BST_Delete(T,num);
	P?printf("Delete Success\n"):printf("illege Delete\n");

	BST_Judge(T);
	return 0;
}

BiTree BST_Create(BiTNode* T, ElemType ch[]){
	int i=0;
	while(ch[i]!=-1){
		T=BST_Insert(T,ch[i++]);
		if(T==NULL){
			printf("Illeged Insert\n");
		}
	}
	return T;
}

BiTNode* BST_Insert(BiTNode* T,ElemType ch){
	int flag=1;
	if(T==NULL){
		T=(BiTNode*)malloc(sizeof(BiTNode));
		T->data=ch;
		T->lchild=NULL;
		T->rchild=NULL;
		flag=0;
	}
		if(ch<T->data){
			T->lchild=BST_Insert(T->lchild,ch);
		}
		if(ch>T->data){
			T->rchild=BST_Insert(T->rchild,ch);
		}
		if(ch==T->data&&flag){
			return NULL;
		}

	return T;
}

BiTNode* BST_Search(BiTNode* T,ElemType ch){
	if(T==NULL){
		return NULL;
	}
	if(ch<T->data){
		return BST_Search(T->lchild,ch);
	}else if(ch>T->data){
		return BST_Search(T->rchild,ch);
	}else{
		return T;
	}
}

BiTNode* BST_Delete(BiTNode* T,ElemType ch){
	if(ch<T->data){
		return BST_Delete(T->lchild,ch);
	}else if(ch>T->data){
		return BST_Delete(T->rchild,ch);
	}else{
		BiTNode *r;
		if(T->lchild==NULL&&T->rchild==NULL){
			free(T);
		}
		if(T->lchild==NULL&&T->rchild!=NULL){
			r=T->rchild;
			T->data=T->rchild->data;
			free(r);
		}
		if(T->lchild!=NULL&&T->rchild==NULL){
			
		}
	}

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
