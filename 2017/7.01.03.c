/**
 * @file 7.01.03.c
 * @Synopsis  结构体+回调函数
 * @author apktool
 * @version 0.1
 * @date 2017-07-01
 */
#include<stdio.h>

void haha(void);
void ahah(void);

/**
 * @Synopsis  定义blk_dev_struct结构体，即struct blk_dev_struct可以认为是一种新的类型
 */
struct blk_dev_struct{
	void (*fun)(void);
};

/**
 * @Synopsis  定义了一个类型为blk_dev_struct类型的变量数组
 */
struct blk_dev_struct blk_dev[2]={
	          /* 这里的NULL有点类似于占位符的意思。*/
	{ NULL }, // 因为这里定义blk_dev有两个元素，因此它有两个大括号括住的两行。
	{ NULL }  // 而每行里面有一个NULL，是因为blk_dev_struct这种“类型”里面只有一个成员
};

int main(int argc, char* argv[]){
	blk_dev[0].fun=haha;
	blk_dev[0].fun();

	blk_dev[1].fun=ahah;
	blk_dev[1].fun();
	return 0;
}

void haha(void){
	printf("hello world\n");
}

void ahah(void){
	printf("hello C\n");
}
