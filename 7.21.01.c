#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<signal.h>
#include<fcntl.h>
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
int execute_command(void);
void get_command(int);
int check(const char* str);

void do_exit(void);
void do_cd(void);
void do_type(void);
void do_about(void);
void do_jobs(void);
void do_kill(void);

typedef void (*cmd_handler)(void);
typedef struct builtin_cmd{
	char* name;
	cmd_handler handler;
}builtin_cmd_t;
builtin_cmd_t builtins[]={
	{ "exit",do_exit },
	{ "cd",do_cd },
	{ "type",do_type },
	{ "about",do_about },
	{ "jobs",do_jobs },
	{ "kill",do_kill },
	{ NULL,NULL }
};

int buildtin(void);

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
	if(buildtin()){
		return 0;
	}
	get_command(0);
}

int execute_command(void){
	if(cmd_count==0){
		return 0;
	}
	if(infile[0]!='\0'){
		cmd[0].infd=open(infile,O_RDONLY);
	}
	if(outfile[0]!='\0'){
		if(append){

		}
	}
	return 0;
}

void get_command(int i){
	int j=0;
	int inword;
	while(*lineptr==' '||*lineptr=='\t'){
		lineptr++;
	}
	cmd[i].args[j]=avptr;
	while(*lineptr!='\0'
			&& *lineptr!=' '
			&& *lineptr!='\t'
			&& *lineptr!='>'
			&& *lineptr!='<'
			&& *lineptr!='|'
			&& *lineptr!='&'
			&& *lineptr!='\n'){
		*avptr++=*lineptr++;
		inword=1;
	}
	*avptr++='\0';
	switch(*lineptr){
		case ' ':
		case '\t':
			inword=0;
			j++;
			break;
		case '<':
		case '>':
		case '|':
		case '&':
		case '\n':
			if(inword==0){
				cmd[i].args[j]=NULL;
			}
			return;
		default:return;
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

int buildtin(void){
	int i=0;
	int found=0;
	while(builtins[i].name!=NULL){
		if(check(builtins[i].name)){
			builtins[i].handler();
			found=1;
			break;
		}
		i++;
	}
	return found;
}

void do_exit(void){
	int Pnum=0;
	node_t* tmp=head->next;
	while(tmp!=NULL){
		Pnum++;
		tmp=tmp->next;
	}
	if(Pnum!=0){
		printf("There are programs in the background,are you sure to exit?y/N\n");
		char c= getchar();
		if(c=='N')
			return ;
		 else
			goto loop;
	}
	loop:
	printf("exit\n");
	exit(EXIT_SUCCESS);
}

void do_cd(void){
	get_command(0);
	int fd;
	fd=open(*(cmd[0].args),O_RDONLY);
	fchdir(fd);
	close(fd);
}

void do_about(void){
	printf("copyright@Mr'Li 2016-7-21");
}
