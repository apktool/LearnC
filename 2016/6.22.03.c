/**
 * @file 6.22.03.c
 * @brief time(),localtime(),gettimeofdat()
 * @author LiWenGang
 * @date 2016-06-28
 */
#include<sys/types.h>
#include<sys/time.h>
#include<stdio.h>
#include<time.h>

int main(int argc,char* argv[]){
	struct timeval start, end;

	long int mics=gettimeofday(&start,NULL);

	time_t now;
	now=time(&now);
	printf("%ld\n",now);

	char buff[50];
	strftime(buff,sizeof(buff),"%Y-%m-%d %H:%M:%S",localtime(&now));
	printf("%s\n",buff);

	long int mice=gettimeofday(&end,NULL);

	printf("%ld\n",mice-mics);
	return 0;
}
