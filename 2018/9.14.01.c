#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(int args, char* argv[])
{
	fd_set rd;
	struct timeval tv;
	int retval;


	FD_ZERO(&rd);
	FD_SET(0, &rd);

	tv.tv_sec = 5;
	tv.tv_usec = 0;
	retval = select(1, &rd, NULL, NULL, &tv);

	if (retval == 0) //超时
	{
		printf("select time out!\n");
	}
	else if (retval == -1) //失败
	{
		perror("fail to select!\n");
	}
	else  //成功
	{
		printf("data is available!\n");
	}

	return 0;
}
