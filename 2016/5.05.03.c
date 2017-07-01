#include<stdio.h>
#include<stdlib.h>

typedef void* SESS;
typedef int ElemType;

typedef struct LNode{
	ElemType data;
	struct LNode *next;	
}LNode, *LinkList;

LinkList CreatList(LNode*);
void ShowList(SESS);

int main(int argc,char* argv[]){
	LNode *head;
	head=(LNode*)malloc(sizeof(LNode));
	head=CreatList(head);
	ShowList((SESS)head);
	return 0;
}

LinkList CreatList(LNode* head){
	LNode *p=NULL;
	ElemType x;
	scanf("%d",&x);
	while(x!=999){
		p=(LNode*)malloc(sizeof(LNode));
		p->data=x;
		p->next=head->next;
		head->next=p;
		scanf("%d",&x);
	}
	return head;
}

void ShowList(SESS sess){
	LNode *head=(LNode*)sess;
	LNode *p=head->next;
	while(p){
		printf("%3d",p->data);
		p=p->next;
	}
	printf("\n");
}
