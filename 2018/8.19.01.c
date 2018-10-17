#include<stdio.h>
#include<stdint.h>

/**
 * sds.h
 */

int main(int argc, char* argv[]) {
	uint8_t u8 = 0;
	printf("%d - %ldByte\n", u8, sizeof(u8));

	uint16_t u16 = 0;
	printf("%d - %ldByte\n", u16, sizeof(u16));

	uint32_t u32 = 0;
	printf("%d - %ldByte\n", u32, sizeof(u32));

	uint64_t u64 = 0;
	printf("%ld - %ldByte\n", u64, sizeof(u64));

	unsigned char flags = 0;
	printf("%d - %ldByte\n", flags, sizeof(flags));
	return 0;
}
