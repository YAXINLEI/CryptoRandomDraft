/*********************************************************************
* Filename:   functions.c
* Author:     Yaxin Lei
* Copyright:
* Disclaimer: This code is presented "as is" without any guarantees.
* Details:    Performs known-answer tests on the corresponding SHA1
	          implementation. These tests do not encompass the full
	          range of available test vectors, however, if the tests
	          pass it is very, very likely that the code is correct
	          and was compiled properly. This code also serves as
	          example usage of the functions.
*********************************************************************/

/*************************** HEADER FILES ***************************/
#include <stdio.h>
#include <memory.h>
#include <string.h>


 
// int * sample_n(int n)
// {

//     BYTE text1[] = {"abc"};
//     printf("%d\n", n);
// 	SHA256_CTX ctx;
// 	int * ptr = (int*) malloc(n * sizeof(int));

// 	for (int i = 0; i < n/8 + 1; i++) {

// 		BYTE buf[SHA256_BLOCK_SIZE];

// 		sha256_init(&ctx);
// 		sha256_update(&ctx, text1, strlen(text1));
// 		sha256_final(&ctx, buf);

// 		for (int j = 0; j < 8; j++) {
// 			ptr[i+j] = ((int)buf[j] << 24) + ((int)buf[j+1] << 16) + ((int)buf[j+2] << 8) + (int)buf[j+3];
// 		}
// 		// How to update the bytes?
// 	}
// 	return(ptr);
// }


int * sample_n(int n)
{
	SHA256_CTX ctx;
	BYTE text1[] = {"abc"};

	int * ptr = (int*) malloc(n * sizeof(int));

	for (int i = 0; i < n/8 + 1; i++) {

		BYTE buf[SHA256_BLOCK_SIZE];

		sha256_init(&ctx);
		sha256_update(&ctx, text1, strlen(text1));
		sha256_final(&ctx, buf);

		for (int j = 0; j < 8; j++) {
			ptr[i+j] = ((int)buf[j] << 24) + ((int)buf[j+1] << 16) + ((int)buf[j+2] << 8) + (int)buf[j+3];
		}
		// How to update the bytes?
	}
	return(ptr);
}