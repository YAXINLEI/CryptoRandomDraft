/*********************************************************************
* Filename:   counter.h
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


#include <stdlib.h>
#include <memory.h>
#include "sha256.c"
#include "counter.c"

struct RandInput{
    BYTE * string;
    float left_bound;       // select random variables from [left_bound, right_bound]
    float right_bound;
    int count;
};



public class counter
{
    private:
        BYTE[] *seed;     //seed value
        int maxCount;    // maximum value
        int count;             // current count

    public Counter(RandInput *var);
    public float next();
    public void skip();
};
