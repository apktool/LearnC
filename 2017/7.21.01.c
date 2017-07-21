/**
 * @file 7.21.01.c
 * @Synopsis  结构体+函数指针
 * @author apktool
 * @version 0.1
 * @date 2017-07-21
 */
#include<stdio.h>

struct tty_struct{
	char word[32];
	void (*write)(struct tty_struct* tty);
};

void hehda(struct tty_struct* tty);

int main(int argc, char* argv[]){
	struct tty_struct tty_table[] = {
		{"hello world" ,hehda },
		{"hello C" ,hehda },
	};

	tty_table[0].write(&tty_table[0]);
	tty_table[1].write(&tty_table[0]);

	return 0;
}

void hehda(struct tty_struct* tty){
	printf("%s\n", tty->word);
}

/**
 *
 * 将结构体自身作为结构体内部回调函数的参数传递
 */
