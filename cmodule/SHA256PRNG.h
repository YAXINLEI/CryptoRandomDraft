//Header
#include "sha256.h"
//class
typedef struct {
    int counter;     // keep track of counter
    int basehash;    
    int curhash;
    int seedlength;

    BYTE *baseseed;
    BYTE *buf;
    SHA256_CTX ctx;
} SHA256PRNG;

SHA256PRNG* SHA256PRNG__create(char* seed); //equivalent to "SHA256PRNG(seed)"
void SHA256PRNG__destroy(SHA256PRNG* self); //equivalent to "delete SHA256PRNG"
char* SHA256PRNG__seed(SHA256PRNG* self, char* seed, int seed_len); //equivalent to "SHA256PRNG-> seed()"
void SHA256PRNG__counter(SHA256PRNG* self, int counter); //equivalent to "SHA256PRNG-> counter()"
void setstate(SHA256PRNG* self, char* baseseed, int counter);


