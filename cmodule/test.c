#include <stdio.h>
#include <stdlib.h>
#include "sha256.c"

void main() {
    printf("Hello \n");

    BYTE text1[] = {"abc"};

    BYTE buf[SHA256_BLOCK_SIZE];
	SHA256_CTX ctx;

	sha256_init(&ctx);
	sha256_update(&ctx, text1, strlen(text1));
	sha256_final(&ctx, buf);

    printf("The integer is %d\n", buf[0]);
    printf("The integer is %d\n", buf[1]);
    printf("The integer is %d\n", buf[2]);
    printf("The integer is %d\n", buf[3]);
    printf("The integer is %d\n", buf[4]);
    printf("The integer is %d\n", buf[5]);
    printf("The integer is %d\n", buf[6]);
    printf("The integer is %d\n", buf[7]);
}