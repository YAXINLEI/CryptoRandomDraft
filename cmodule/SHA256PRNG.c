
//Header Files
#include <stdlib.h>
#include <memory.h>
#include "SHA256PRNG.h"
#include "sha256.h"


//Constructor
void SHA256PRNG__init(SHA256PRNG* self, char* seed) {
    self->baseseed = seed;
    self->counter = 0;
}

//equivalent to "SHA256PRNG(seed)"
SHA256PRNG* SHA256PRNG__create(char* seed){
    SHA256PRNG* result = (SHA256PRNG*) malloc(sizeof(SHA256PRNG));
    Point__init(result, seed);
    return result;
}

//equivalent to "delete SHA256PRNG"
void SHA256PRNG__destroy(SHA256PRNG* self) {
    if (self) {
        free(self);
    }
}

//equivalent to "SHA256PRNG-> seed()"
char* SHA256PRNG__seed(SHA256PRNG* self, char* seed) {
    return self->baseseed = seed;
} 

//equivalent to "SHA256PRNG-> counter()"
int SHA256PRNG__counter(SHA256PRNG* self, int counter) {
    return self->counter = counter;
}



int _basehash(SHA256PRNG* self) {
    if(self->basehash) {//basehash is not None/null
        self->hashinput = 0;
    } else {
        self->hashinput = 0;
    }
}

void setstate(SHA256PRNG* self, char* baseseed, int counter) {

}

int* getstate(SHA256PRNG* self) {

}

void jumpahead(SHA256PRNG* self, int n) {

}

void next(SHA256PRNG* self) {
    jumpahead(self, 1);
}

int nextRandom(SHA256PRNG* self) {

}

int* nextRandom(SHA256PRNG* self, int size) {

}

int* randint_trunc(SHA256PRNG* self, int a, int b, int size) {
    
}

int* getrandbits(SHA256PRNG* self, int k) {
    
}

int* randbelow_from_randbits(SHA256PRNG* self, int n) {

}

int* randint(SHA256PRNG* self, int a, int b, int size) {
    
}


