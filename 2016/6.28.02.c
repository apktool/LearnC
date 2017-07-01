//fopen(),fwrite(),fread(),fgets()
#include<stdio.h>

int main(int argc, char* argv[]){
	FILE *fp;
	fp=fopen("123.txt","rw+");
	if(fp==NULL){
		printf("Open failed\n");
	}

	size_t numRead;
	char buff[]="hello LaTex";
	numRead=fwrite(buff,1,sizeof(buff),fp);
	printf("%ld\n",numRead);
	while(!feof(fp)){
		//char* s;
		//s=fgets(buff,sizeof(buff),fp);
		numRead=fread(buff,1,sizeof(buff),fp);
		printf("%ld\n",numRead);
		printf("%s\n",buff);
	}
	return 0;
}
