#include<sys/types.h>
#include<time.h>
#include<stdio.h>

int main(int argc, char* argv[]){
	time_t now;
	now=time(&now);
	printf("%ld\n",now);

	char buf[50];
	strftime(buf,sizeof(buf),"%Y-%m-%d %H:%M:%S",localtime(&now));
	printf("%s\n",buf);

	return 0;
}
