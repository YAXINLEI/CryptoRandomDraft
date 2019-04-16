/*********************************************************************
* Filename:   counter.c
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
#include <counter.h>
#include <sha256.h>




public class Counter
{
    private BYTE seed[];     //seed value
    private final int maxCount;    // maximum value
    private int count;             // current count
    private float left;
    private float right;

    public Counter(RandInput *var){
        if (var->string & 1) {
            seed = var->string;
        } else {
            seed = {"abc"};
        }

        count = 0;
        maxCount = var->count;
    }
    public float next();
    public void skip();
}


void main{
    RandInput temp = new RandInput;
    temp->count = 30;
    printf("%d/n", temp->count)
}