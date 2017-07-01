//操纵动态库
//gcc -Wall -std=c11 5.28.03.c -ldl -o temp
#include<stdio.h>
#include<stdlib.h>
#include<dlfcn.h>

typedef char ElemType;
typedef struct BiTNode{
	ElemType data;
	struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

typedef BiTree (*pFunc1)(BiTNode*);
typedef void (*pFunc2)(BiTNode*);

int main(int argc, char* argv[]){
	void* handle=NULL;
	handle=dlopen("libBTree.so",RTLD_LAZY);
	if(!handle){
		printf("%s",dlerror());
	}
	BiTNode* T=(BiTNode*)malloc(sizeof(BiTNode*));
	
	pFunc1 p;
	p=(BiTree (*)(BiTNode *))dlsym(handle,"CreateBiTree");
	T=p(T);

	pFunc2 q;

	q=(void (*)(BiTNode*))dlsym(handle,"PreOrder");
	q(T);
	printf("\n");

	q=(void (*)(BiTNode*))dlsym(handle,"InOrder");
	q(T);
	printf("\n");

	q=(void (*)(BiTNode*))dlsym(handle,"PostOrder");
	q(T);
	printf("\n");

	q=(void (*)(BiTNode*))dlsym(handle,"LevelOrder");
	q(T);
	printf("\n");

	dlclose(handle);
	return 0;
}
