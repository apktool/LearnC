//生成动态库
//gcc -fPIC -shared 5.28.02.c -o libBTree.so
#include<stdio.h>
#include<stdlib.h>

#define MaxSize 100

typedef char ElemType;
typedef struct BiTNode{
	ElemType data;
	struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

BiTNode* CreateBiTree(BiTNode*);
void PreOrder(BiTNode*);
void InOrder(BiTNode*);
void PostOrder(BiTNode*);
void LevelOrder(BiTNode*);

typedef struct SqStack{
	BiTNode* data[MaxSize];
	int top;
}SqStack;

void InitStack(SqStack*);
void Push(SqStack*,BiTNode*);
BiTNode* Pop(SqStack*);
BiTNode* GetTop(SqStack*);
int IsEmptyStack(SqStack*);

typedef struct SqQueue{
	BiTNode* data[MaxSize];
	int front, rear;
}SqQueue;


void InitQueue(SqQueue*);
void EnQueue(SqQueue*, BiTNode*);
BiTNode* DeQueue(SqQueue*);
int IsEmptyQueue(SqQueue*);

/*
int main(int argc, char* argv[]){
	BiTNode *T=(BiTNode*)malloc(sizeof(BiTNode));
	T=CreateBiTree(T);
	PreOrder(T);printf("\n");
	InOrder(T);printf("\n");
	PostOrder(T);printf("\n");
	LevelOrder(T);printf("\n");
	return 0;
}
*/

BiTree CreateBiTree(BiTNode* T){
	ElemType x;
	scanf("%c",&x);
	if(x=='#'){
		return T;
	}else{
		T=(BiTNode*)malloc(sizeof(BiTNode));
		T->data=x;
		T->lchild=CreateBiTree(T->lchild);
		T->rchild=CreateBiTree(T->rchild);
	}
	return T;
}

void PreOrder(BiTNode* T){
	SqStack S;
	InitStack(&S);

	BiTNode* p=T;
	Push(&S,p);
	while(IsEmptyStack(&S)!=0){
		p=Pop(&S);
		printf("%c",p->data);
		if(p->rchild!=NULL){
			Push(&S,p->rchild);
		}
		if(p->lchild!=NULL){
			Push(&S,p->lchild);
		}
	}
}

void InOrder(BiTNode* T){
	SqStack S;
	InitStack(&S);

	BiTNode* p=T;
	
	while(p||IsEmptyStack(&S)!=0){
		if(p!=NULL){
			Push(&S,p);
			p=p->lchild;
		}else{
			p=Pop(&S);
			printf("%c",p->data);
			p=p->rchild;
		}
	}
}

void PostOrder(BiTNode* T){
	SqStack S;
	InitStack(&S);

	BiTNode *p=T;
	BiTNode *r=NULL;

	while(p||IsEmptyStack(&S)!=0){
		if(p!=NULL){
			Push(&S,p);
			p=p->lchild;
		}else{
			p=GetTop(&S);
			if(p->rchild!=NULL&&p->rchild!=r){
				p=p->rchild;
				Push(&S,p);
				p=p->lchild;
			}else{
				p=Pop(&S);
				printf("%c",p->data);
				r=p;
				p=NULL;
			}
		}
	}
}

void LevelOrder(BiTNode* T){
	SqQueue Q;
	InitQueue(&Q);

	BiTNode *p=T;
	EnQueue(&Q,p);

	while(IsEmptyQueue(&Q)!=0){
		p=DeQueue(&Q);
		printf("%c",p->data);
		if(p->lchild!=NULL){
			EnQueue(&Q,p->lchild);
		}
		if(p->rchild!=NULL){
			EnQueue(&Q,p->rchild);
		}
	}
}

void InitStack(SqStack* S){
	S->top=-1;
}

void Push(SqStack* S, BiTNode* T){
	if(S->top==MaxSize-1){
		return;
	}
	S->data[++S->top]=T;
}

BiTNode* Pop(SqStack* S){
	if(S->top==-1){
		return NULL;
	}
	return S->data[S->top--];

}

BiTNode* GetTop(SqStack* S){
	if(S->top==-1){
		return NULL;
	}
	return S->data[S->top];
}

int IsEmptyStack(SqStack* S){
	if(S->top==-1){
		return 0;
	}
	return -1;
}

void InitQueue(SqQueue* Q){
	Q->front=0;
	Q->rear=0;
}

void EnQueue(SqQueue* Q, BiTNode* T){
	if((Q->rear+1)%MaxSize==Q->front){
		return;
	}
	Q->data[Q->rear++]=T;
}

BiTNode* DeQueue(SqQueue* Q){
	if(Q->front==Q->rear){
		return NULL;
	}
	return Q->data[Q->front++];
}

int IsEmptyQueue(SqQueue* Q){
	if(Q->front==Q->rear){
		return 0;
	}
	return -1;
}
