/**
 * @file temp.c
 * @Synopsis  gets, fgets
 * @author apktool
 * @version 0.1
 * @date 2017-07-27
 */
#include <stdio.h>

void func(){
    char array[10];
    //fgets(array, 5, stdin);
	gets(array);
	printf("%s\n", array);
}

int main(int argc, char **argv){
    func();
}

/*
 * fgets之所以比gets安全，主要是因为：
 *
 * 以上例为例，比如我输入的是: He once a ture love of mine (共27字符)
 * array最后被赋值的标准是array定义的大小和fgets中限制大小的最小值
 * 而多出字符最后并不会被赋值到array
 *
 * 有时为了能够让fgets中定义的限制大小和array中的大小存在关联，会写成
 * fgets(array, sizeof(array), stdin);
 * 
 ************************
 * 
 * gets中如果输入的字符超过字符串定义大小，则会出现下述错误
 *
 * *** stack smashing detected ***: ./a.out terminated
 *
 * 可以考虑编译时加入-fno-stack-protector来取消编译器对变量的保护
 * 但是会出现
 * 10803 segmentation fault (core dumped)
 *
 */
