#include<sys/types.h>
#include<signal.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAXLINE 1024 //输入行的最大长度
#define MAXNAME 100 //IO重定向文件名的最大长度
#define PIPELINE 5 //一个管道行中简单命令行的最多个数

typedef struct node_t{
	pid_t pid;
	char *backcn[20];
	struct node_t *next;
}node_t;

typedef struct command{
	char* args[MAXNAME+1];
	int infd;
	int outfd;
}cmd_t;

node_t *head;
cmd_t cmd[PIPELINE];

char cmdline[MAXLINE+1];
char avline[MAXLINE+1];
char* lineptr;
char* avptr;
char infile[MAXNAME+1];
char outfile[MAXNAME+1];

int cmd_count;
int backgnd;
int append;
int lastpid;

void sigint_handler(int sig);
void shell_loop(void);
void init(void);
int read_command(void);
int parse_command(void);
int check(const char* str);

int main(int argc, char* argv[]){
	head=(node_t*)malloc(sizeof(node_t));
	head->next=NULL;

	signal(SIGINT,sigint_handler);
	signal(SIGQUIT,SIG_IGN);

	shell_loop();
	return 0;
}

void sigint_handler(int sig){
	printf("\n[minishell]$ ");
	fflush(stdout);
}

void shell_loop(void){
	while(1){
		init();
		if(read_command()==-1){
			break;
		}
		parse_command();
	}
}

void init(void){
	memset(cmd,0,sizeof(cmd));
	for(int i=0;i<PIPELINE;i++){
		cmd[i].infd=0;
		cmd[i].outfd=1;
	}
	memset(cmdline,0,sizeof(cmd));
	memset(avline,0,sizeof(avline));
	lineptr=cmdline;
	avptr=avline;
	memset(infile,0,sizeof(infile));
	memset(outfile,0,sizeof(outfile));
	cmd_count=0;
	backgnd=0;
	append=0;
	lastpid=0;
	fflush(stdout);
}

int read_command(void){
	if(fgets(cmdline,MAXLINE,stdin)==NULL){
		return -1;;
	}
	return 0;
}

int parse_command(void){
	if(check("\n")){
		return 0;
	}
}

int check(const char* str){
	char* p;
	while(*lineptr==' '||*lineptr=='\t'){
		lineptr++;
	}
	p=lineptr;
	while(*str!='\0'&&*str==*p){
		str++;
		p++;
	}
	if(*str=='\0'){
		lineptr=p;
		return 1;
	}
	return 0;
}
