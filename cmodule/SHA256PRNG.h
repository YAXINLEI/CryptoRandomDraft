//Header
#include "sha256.h"
//class
typedef struct {
    char* baseseed;
    int counter;
    int basehash;
    SHA256_CTX ctx;
} SHA256PRNG;

SHA256PRNG* SHA256PRNG__create(char* seed); //equivalent to "SHA256PRNG(seed)"
void SHA256PRNG__destroy(SHA256PRNG* self); //equivalent to "delete SHA256PRNG"
char* SHA256PRNG__seed(char* seed); //equivalent to "SHA256PRNG-> seed()"
int SHA256PRNG__counter(int counter); //equivalent to "SHA256PRNG-> counter()"


