/*****************
 * Sampling with or without weights, with or without replacement
 * ****************/



//headers
#include <stdio.h>
#include <memory.h>
#include <string.h>
#include <stdbool.h>
#include "SHA256PRNG.h"


SHA256PRNG* get_prng() {

}


/******  Main callable sampling methods *******/

int* random_sample(int* a, int size, bool replace, int* p, char* method, SHA256PRNG* prng) {
    //if sampling from an array

}
int* random_sample(int a, int size, bool replace, char* method, SHA256PRNG* prng) {
    //if sampling size integers

    if(strcmp(method, "Fisher-Yates") == 0) {
        //always without replacement
        return fykd_sample(a, size, prng);
    } else if(strcmp(method, "PIKK" == 0)) {
        //always without replacement
        return pikk(a, size, prng);
    } else if(strcmp(method, "recursive" == 0)) {
        //always without replacement
        return recursive_sample(a, size, prng);
    } else if(strcmp(method, "Waterman_R" == 0)) {
        //always without replacement
        return waterman_r(a, size, prng);
    } else if(strcmp(method, "Vitter_Z" == 0)) {
        //always without replacement
        return vitter_z(a, size, prng);
    } else if(strcmp(method, "sample_by_index" == 0)) {
        //always without replacement
        return sample_by_index(a, size, prng);
    } else if(strcmp(method, "Exponential" == 0)) {
        if(replace) {
            return exponential_sample(a, size, prng);
        } else {
            return exponential_sample(a, size, prng);
        }
    } else if(strcmp(method, "Elimination" == 0)) {
        if(replace) {
            return elimination_sample(a, size, prng);
        } else {
            return elimination_sample(a, size, prng);
        }
        
    } else {
        //invalid input: however this should not be the case 
        //bc this should by caught in the python portion
    }
}

int* random_permutation(char* method, SHA256PRNG* prng) {

}


/*******  SAMPLING FUNCTIONS  ******/
int* fykd_sample(int n, int k, SHA256PRNG* prng) {
    //problem with variable length arrays currently
    //how to create an array with variable length?
    int a[n];
    for(int i = 0; i < n; i++) {
        a[i] = i;
    }
    int rand[k] = random(prng, k);
    int ind[k];
    for(int i = 0; i < k; i++) {
        ind[i] = i;
    }
    int JJ[];
    for(int i = 0; i < k; i++) {
        int J = JJ[i];
        a[i], a[J] = a[J], a[i];
    }
    int a2[k];
    memcpy(a2, &a[1], k*sizeof(*a));
    return a2;
}

int* pikk(int n, int k, SHA256PRNG* prng) {
    int rand_n[n] = random(prng, n);
    int result[k];
    memcpy(result, &rand_n[1], k*sizeof(*rand_n));
    return result;
}

int* recursive_sample(int n, int k, SHA256PRNG* prng) {
    if(k == 0) {
        int* empty;
        return empty;
    } else {
        int* S = recursive_sample(n-1, k-1, prng);
        int i = randint(1, n+1);
        int result[k];
        if(containsElement(i, S)) {
            for(int j = 0; j < k-1; j++) {
                result[j] = S[j];
            } 
            result[k-1] = n;
        } else {
            for(int j = 0; j < k-1; j++) {
                result[j] = S[j];
            } 
            result[k-1] = i;
        }
        return result;
    }
}
//helper function for recursive sampling, determines if element is in array
bool containsElement(int element, int* array) {
    int temp = 0;
    for(int i = 0; i < sizeof(array)/sizeof(temp); i++) {
        if(array[i] == element) {
            return true;
        }
    }
    return false;
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
