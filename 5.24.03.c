//二叉排序树Binary Search Tree[BST]
#include<stdio.h>
#include<stdlib.h>
#define MaxSize 15
typedef int ElemType;
typedef struct BiTNode{
	ElemType data;
	struct BiTNode *lchild, *rchild;
}BiTNode,*BiTree;

BiTNode* CreateBiTree(BiTNode*,ElemType*);
int BST_Insert(BiTNode**,ElemType);
int BST_Search(BiTNode*,ElemType);
int BST_Delete(BiTNode*,ElemType);
void BST_Judge(BiTNode*);

void PreOrder(BiTNode*);
void InOrder(BiTNode*);

int main(int argc,char* argv[]){
	printf(">> %s|%s|%d Complete\n",__FILE__,__FUNCTION__,__LINE__);
	ElemType ch[MaxSize]={
		9,5,10,10,3,7,11,3,6,8,2,4,-1	
	};

	BiTNode* T=NULL;
	T=CreateBiTree(T,ch);

	BST_Judge(T);

	int flag,no=1;
	
	flag=BST_Search(T,no);
	flag?printf("No Find %d, ",no):printf("Find %d, ",no);
	flag=BST_Delete(T,no);
	flag?printf("Delete Failed,Have no '%d'\n",no):printf("Delete Success\n");

	BST_Judge(T);

	return 0;
}

BiTNode* CreateBiTree(BiTNode* T,ElemType ch[]){
	printf(">> %s|%s|%d Complete\n",__FILE__,__FUNCTION__,__LINE__);
	int flag;
	for(int i=0;i<MaxSize&&ch[i]!=-1;i++){
		flag=BST_Insert(&T,ch[i]);
		if(flag){
			printf("Insert Failed, Have '%d'\n",ch[i]);
			break;
		}
	}
	return T;
}

int BST_Insert(BiTNode** T,ElemType ch){
	if(*T==NULL){
		*T=(BiTNode*)malloc(sizeof(BiTNode));
		(*T)->data=ch;
		(*T)->lchild=NULL;
		(*T)->rchild=NULL;
	}
	if(ch==(*T)->data){
		return -1;
	}else if(ch<(*T)->data){
		return BST_Insert(&(*T)->lchild,ch);
	}else{
		return BST_Insert(&(*T)->rchild,ch);
	}
	return 0;
}

int BST_Search(BiTNode* T, ElemType ch){
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
	BiTNode *p=T;
	BiTNode *pre=NULL;

	while(p->data!=ch){
		if(p->lchild==NULL&&p->rchild==NULL){
			return -1;
		}

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

	//该节点为叶子结点
	if(p->lchild==NULL&&p->rchild==NULL){
		if(p->data<pre->data){
			pre->lchild=NULL;
		}else{
			pre->rchild=NULL;
		}
		free(p);
	}

	//该节点只有左子树而没有右子树
	if(p->lchild!=NULL&&p->rchild==NULL){
		if(p->data<pre->data){
			pre->lchild=p->lchild;
		}else{
			pre->rchild=p->lchild;
		}
		free(p);
	}

	//该节点只有右子树而没有左子树
	if(p->lchild==NULL&&p->rchild!=NULL){
		if(p->data<pre->data){
			pre->lchild=p->rchild;
		}else{
			pre->rchild=p->rchild;
		}
		free(p);
	}

	//该节点同时拥有左右子树
	if(p->lchild!=NULL&&p->rchild!=NULL){
		BiTNode *r=p;
		p=p->rchild;
		while(p->lchild!=NULL){
			pre=p;
			p=p->lchild;
		}
		r->data=p->data;

		if(p->data<pre->data){
			pre->lchild=r->lchild;
		}else{
			pre->rchild=p->rchild;
		}

		free(p);
	}

	return 0;
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

void BST_Judge(BiTNode* T){
	PreOrder(T);
	printf("\n");
	InOrder(T);
	printf("\n");
}
