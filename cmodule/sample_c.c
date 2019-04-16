/*****************
 * Sampling with or without weights, with or without replacement
 * ****************/



//headers
#include <stdio.h>
#include <memory.h>
#include <string.h>
#include "SHA256PRNG.h"


SHA256PRNG* get_prng() {

}


/******  Main callable sampling methods *******/
int* random_sample(int size, bool replace, int* p, char* method, SHA256PRNG* prng) {

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
