/*****************
 * Sampling with or without weights, with or without replacement
 * ****************/



//headers
#include <stdio.h>
#include <memory.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
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
    /**
     * Use fykd to sample k out of 1, ..., n without replacement
     * 
     * Parameters:
     * -----------
     * n : int
     *     Population size
     * k : int
     *     Desired sample size
     * prng: SHA256PRNG
     *     the SHA256PRNG that generates the random numbers
     * Returns:
     * --------
     * pointer to array of randomized indices 
     * */
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
    /**
     * PIKK Algorithm: permute indices and keep k to draw a sample 
     * from 1, ..., n without replacement
     * (Assumes indexing starting at 1)
     * 
     * Parameters:
     * ----------
     * n : int
     *     Population size
     * k : int
     *     Desired sample size
     * prng: SHA256PRNG
     *     the SHA256PRNG that generates the random numbers
     * Returns:
     * --------
     * pointer to array of randomized indices 
     * */
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
    //fill the reservoir
    int S[k];
    for(int i = 0; i < k; i++) {
        S[i] = i+1;
    }
    for(int t = k+1; t < n+1; t++) {
        int i = randint(1, t+1);
        if(i <= k) {
            S[i-1] = t;
        }
    }
    return S;
}

int* vitter_z(int n, int k, SHA256PRNG* prng) {

}

int* sample_by_index(int n, int k, SHA256PRNG* prng) {
    int nprime = n;
    int S[k];
    int currIndexS = 0;
    int Pop[n]; //Pop = [1, 2, 3, ..., n]
    int currIndexPop = 0;
    for(int i = 0; i < n; i++) {
        Pop[i] = i+1;
    }
    while(nprime > n-k) {
        int w = randint(1, nprime + 1);
        int j = Pop[w-1];
        S[currIndexS] = j;//append j to current end of S
        currIndexS ++;
        int lastvalue = Pop[currIndexPop];//the last value from Pop
        currIndexPop ++;
        if(w < nprime) {
            Pop[w-1] = lastvalue;
        }
        nprime--;
    }
    return S;
}

int* elimination_sample(int k, int* weights, bool replace, SHA256PRNG* prng) {
    /**
     * 
     **/
    int n = sizeof(weights)/sizeof(weights[0]);//length of weights/array to choose from
    long totalSum = 0;
    for(int i = 0; i < n; i++) {
        totalSum += weights[i];
        if (weights[i] < 0) {
            return;//raise value error? 
        }
    }
    if(replace) {//with replacement
        float cumulativeSum[n];//weights cumulative and normalized weights
        float currCumulativeSum = 0;
        for(int i = 0; i < n; i++) {
            cumulativeSum[i] = currCumulativeSum + weights[i]/totalSum;
            currCumulativeSum += cumulativeSum[i];
        }
        int toSampleFrom[k];
        for(int i = 0; i < k; i++) {
            toSampleFrom[k] = i;
        }
        int sam[k] = random(prng, toSampleFrom);
        int result[k];
        for(int i = 0; i < k; i++) {
            result[i] = sam[i] + 1;//?
        }
    } else {//no replacement
        int* weights_left = memccpy(weights_left, weights, n, sizeof(int));
        int* indices_left[n];
        helperRange(indices_left, n);
        for(int i = 0; i < k; i++) {

        }


    }
    
}

int* exponential_sample(int k, int* weights, SHA256PRNG* prng) {
    int n = sizeof(weights)/sizeof(weights[0]);//length of weights/array to choose from
    int result[k];
    for(int i = 0; i < n; i++) {
        if (weights[i] < 0) {
            return;//raise value error? 
        }
    }
    if(k > n) {//sample size larger than pop in sample w/o repl
        return; //raise value error?
    } else if(k == n) {
        //just return all indices (0, 1, ..., n)
        helperRange(result, k);
        return result;
    } else {
        int sam[n] = random(prng, n);
        
        int sample[k];
        return sample;
    }
}


//helper: returns a list 1, 2, ..., n
void helperRange(int* location, int n) {
    for(int i = 0; i < n; i++) {
        location[i] = i;
    }
}
