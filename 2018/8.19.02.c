#include<stdio.h>

/**
 * __attribute__ ((packed)) 的作用就是告诉编译器取消结构在编译过程中的优化对齐,按照实际占用字节数进行对齐，是GCC特有的语法。这个功能是跟操作系统没关系，跟编译器有关
 *
 *
 */

struct __attribute__ ((__packed__)) sdshdr5 {
	unsigned char flags;
	char buf[];
};

int main(int argc, char* argv[]) {
	printf("%d\n", __GNUC__);

	struct sdshdr5 tp;
	printf("%ld\n", sizeof(tp));

	char a[] = "Hello world";
	printf("%ld\n", sizeof(a));
	return 0;
}
