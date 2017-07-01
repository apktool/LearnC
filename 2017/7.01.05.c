/**
 * @file 7.01.05.c
 * @Synopsis 8421BCD码转十进制
 * @author apktool
 * @version 0.1
 * @date 2017-07-01
 */
#include<stdio.h>

#define BCD_TO_BIN(val) ((val)=((val)&15) + ((val)>>4)*10)

int main(int argc, char* argv[]){
	int a=20;
	unsigned int temp=BCD_TO_BIN(a);
	printf("%X\t%u\n", temp, temp);
	return 0;
}

/*
 * BCD: 20 == 0001 0100
 *
 * Bin: 20 == 0001 0100(BCD) -> 0000 0100 + 0000 0001 * 10 -> 4+10 = 0001 0100 == 14(DEC)
 *
 * DEC: 14
 */
