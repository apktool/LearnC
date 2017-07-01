/**
 * @file 10.09.02.c
 * @brief 随机生成某个范围内不重复的随机数
 * @author LiWenGang
 * @date 2016-10-09
 */
#include<stdio.h>
#include<stdlib.h>

#define NUM 100

int main(int argc, char* argv[]){
	int array[NUM];
	for(int i=0;i<NUM;i++){
		array[i]=i;
	}

	int tmp;
	for(int i=0;i<NUM;i++){
		tmp=rand()%(NUM-i);
		array[i]=array[i]^array[tmp];
		array[tmp]=array[i]^array[tmp];
		array[i]=array[i]^array[tmp];
	}

	/*
	//冒泡排序
	for(int i=0;i<NUM;i++){
		for(int j=i+1;j<NUM;j++){
			if(array[i]>array[j]){
				array[i]=array[i]^array[j];
				array[j]=array[i]^array[j];
				array[i]=array[i]^array[j];
			}
		}
	}
	*/

	for(int i=0;i<NUM;i++){
		if(i%10==0){
			printf("\n");
		}
		printf("%5d",array[i]);
	}
	printf("\n");
	return 0;
}

/*
 * 如果使用rand()函数生成随机数，无论怎么取都有可能出现重复的数字。
 * 因此考虑对数组依次按照下标赋值，然后对数组下标进行重新排序，同样可以导致数组数据随机，但数据绝对不会重复
 */
