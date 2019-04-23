
//Header Files
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <math.h>
#include <string.h>

#include "SHA256PRNG.h"
#include "sha256.h"


//Constructor
void SHA256PRNG__init(SHA256PRNG* self, char* seed, int seed_len) {
    self = malloc(sizeof(SHA256PRNG));
    self->baseseed = malloc(seed_len+1);    // one extra space for the null pointer

    for (int i = 0; i <= seed_len; i += 1) {
        self->baseseed[i] = seed[i];
    }
    self->counter = 0;
}


// //equivalent to "SHA256PRNG(seed)"
// SHA256PRNG* SHA256PRNG__create(char* seed){
//     SHA256PRNG* result = (SHA256PRNG*) malloc(sizeof(SHA256PRNG));
//     Point__init(result, seed);
//     return result;
// }

//equivalent to "delete SHA256PRNG"
void SHA256PRNG__destroy(SHA256PRNG* self) {
    // Free everything in the SHA256PRNG struct
    free(self->baseseed);
    free(self);
}

//equivalent to "SHA256PRNG-> seed()"
char* SHA256PRNG__seed(SHA256PRNG* self, char* seed, int seed_len) {
    for (int i = 0; i < seed_len; i += 1) {
        self->baseseed[i] = seed[i];
    }
    self->seedlength = seed_len;
    return seed;
} 


//equivalent to "SHA256PRNG-> counter()"
void SHA256PRNG__counter(SHA256PRNG* self, int counter) {
    self->counter = counter;
}



void _basehash(SHA256PRNG* self) {
    if(self->basehash) {//basehash is not None/null
        BYTE* buf = malloc(sizeof(SHA256_BLOCK_SIZE));

	    sha256_init(&(self->ctx));
	    sha256_update(&(self->ctx), self->baseseed, self->seedlength);
	    sha256_final(&(self->ctx), buf);
        self->buf = buf;
        self->basehash = 0;
    } else {
        self->basehash = 0;
    }
}


int main(){
    SHA256PRNG* temp;
    char *string = {"abc"};
    SHA256PRNG__init(temp, string, 3);
    SHA256PRNG__counter(temp, 3);
    _basehash(temp);
    printf("%d/n", temp->buf[0]);
    SHA256PRNG__destroy(temp);
    return temp->counter;
}





void setstate(SHA256PRNG* self, char* baseseed, int counter) {
    free(self->baseseed);
    self->baseseed = malloc(strlen(baseseed));

    for (int i = 0; i < strlen(baseseed); i += 1) {
        self->baseseed[i] = baseseed[i];
    }

    self->counter = counter;
}

//original getstate split into two functions below:
BYTE* getStateBaseseed(SHA256PRNG* self) {
    return self->baseseed;
}
int* getStateCounter(SHA256PRNG* self) {
    return &(self->counter);
}

void jumpahead(SHA256PRNG* self, int n) {
    self->counter = self->counter + n;
    self->basehash;
}

void next(SHA256PRNG* self) {
    jumpahead(self, 1);
}

BYTE* nextRandom(SHA256PRNG* self) {
    BYTE hash_output[] = &(self->ctx);//problem here
    next(self);
    return hash_output;
}

int random(SHA256PRNG* self, int size) {
    if(!size) {//size is NULL
        BYTE* hash_output = nextRandom(self);
        return *((int*) (hash_output));
    } else {
        int hash_output[size];//why? [5] is okay...
        for(int i = 0; i < size; i++) {
            hash_output[i] = *((int*) (nextRandom(self)));
        }
        return hash_output;
    }
}
int random(SHA256PRNG* self, int size[]) {
    if(!size) {//size is NULL
        BYTE* hash_output = nextRandom(self);
        return *((int*) (hash_output));
    } else {
        //TODO: implement random (like above) but for a length(size) dimensional matrix
        //How to do this with an arbitrary dimensional matrix?
        //for dimension 2 (ie size = (10, 20))
        int hash_output[10][20];
        for(int i = 0; i < 10; i++) {
            for(int j = 0; j < 20; j++) {
                hash_output[i][j] = *((int*) (nextRandom(self)));
            }
        }
        return hash_output;
    }
}

int randint_trunc(SHA256PRNG* self, int a, int b, int size) {
    if(size == NULL) {
        return a + *((int*) nextRandom(self)) % (b - a);
    } else {
        int hash_output[size];
        for(int i = 0; i < size; i++) {
            hash_output[i] = a + *((int*) nextRandom(self)) % (b - a);
        }
        return hash_output;
    }
}

BYTE* getrandbits(SHA256PRNG* self, int k) {
    BYTE *result;
    
    if (k/8 == 0) {
        BYTE result[SHA256_BLOCK_SIZE * k/8];
    } else {
        BYTE result[SHA256_BLOCK_SIZE * k/8 + 1];
    }
    if (k > SHA256_BLOCK_SIZE) {
        for (int i = 0; i < k/256; i++) {
            BYTE buf[SHA256_BLOCK_SIZE];
            sha256_init(&(self->ctx));
            sha256_update(&(self->ctx), self->baseseed, strlen(self->baseseed));
            sha256_final(&(self->ctx), buf);
            self->basehash = 0;

            memcpy(result[i], buf, SHA256_BLOCK_SIZE);
        }
    } else {
        BYTE buf[SHA256_BLOCK_SIZE];
        sha256_init(&(self->ctx));
        sha256_update(&(self->ctx), self->baseseed, strlen(self->baseseed));
        sha256_final(&(self->ctx), buf);
        memcpy(result, buf, k);
    }
    return result;
    
}

BYTE* randbelow_from_randbits(SHA256PRNG* self, int n) {
    int k = (int) ceil(log2((int) (n-1))); //number of bits
    BYTE* r = getrandbits(self, k);
    while((int) (int*) r  >= n) {
        r = getrandbits(self, k);
    }
    return r;
}

int* randint(SHA256PRNG* self, int a, int b, int size) {
    if( !(a<=b)) {
        return NULL;
    } 
    if(size == NULL) {
        return a + randbelow_from_randbits(self, b-a);
    } else {
        int hash_output[size];
        for(int i = 0; i < size; i++) {
            hash_output[i] = a + *((int*) randbelow_from_randbits(self, (b-a))) % (b - a);
        }
        return hash_output;
    }
}



int* randint(int n)
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



SHA256_CTX* helperHash(BYTE input[]) {
    //will find the hash of some input
    //thought this would help, but it isn't used
    BYTE buf[SHA256_BLOCK_SIZE];
	SHA256_CTX ctx;

	sha256_init(&ctx);
	sha256_update(&ctx, input, strlen(input));
	sha256_final(&ctx, buf);
    return(&ctx);
}
