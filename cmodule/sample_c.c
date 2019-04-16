/*****************
 * Sampling with or without weights, with or without replacement
 * ****************/



//headers
#include <stdio.h>
#include <memory.h>
#include <string.h>
#include <stdbool.h>
#include "SHA256PRNG.h"


SHA256PRNG* get_prng(char* seed) {
    //original allowed seed to be either a string or a integer
    //need 2 functions to account for that
    return SHA256PRNG__create(seed);
}
SHA256PRNG* get_prng(int seed) {
    return SHA256PRNG__create(itoa(seed));//itoa converts int to string
}


/******  Main callable sampling methods *******/
int* random_sample(void* a, int size, bool replace, int* p, char* method, SHA256PRNG* prng) {
    
}

int* random_permutation(char* method, SHA256PRNG* prng) {

}


/*******  SAMPLING FUNCTIONS  ******/
int* fykd_sample(int n, int k, SHA256PRNG* prng) {

}

int* pikk(int n, int k, SHA256PRNG* prng) {

}

int* recursive_sample(int n, int k, SHA256PRNG* prng) {

}

int* waterman_r(int n, int k, SHA256PRNG* prng) {

}

int* vitter_z(int n, int k, SHA256PRNG* prng) {

}

int* sample_by_index(int n, int k, SHA256PRNG* prng) {

}

int* elimination_sample(int n, int k, SHA256PRNG* prng) {

}

int* exponential_sample(int n, int k, SHA256PRNG* prng) {

}
