## Cryptorandom with C module

File Structure:
```
CryptoRandomDraft/
    crytorandom.py --> cryptorandom.pyx
    sample.py      --> sample.pyx
    cmodule/
        SHA256PRNG.h
        SHA256PRNG.c
            SHA256
            __init__
            __repr__
            _basehash
            seed
            setstate
            getstate
            jumpahead
            next
            nextRandom
            random
            randint_trunc
            getrandbits
            randbelow_from_randbits
            randint

        sample_c.c
            get_prng
            random_sample
            random_permutation
            fykd_sample
            pikk
            recursive_sample
            waterman_r
            vitter_z
            sample_by_index
            elimination_sample
            exponential_sample
            
        sha256.c
            sha256_init
            sha256_update
            sha256_final
```
For each function f(x) in the original `cryptorandom.py`, we would define the function f(x) in `cryptorandom.pyx` as:
```
f(x):
    cmodule::cryptorandom_c.f(x)
```
where the actual implementation of `f(x)` is in `cmodule/cryptorandom_c.c` and the cython .pyx file just calls the c function.


#### Notes we might want to remember:
+ doing `#include "sha256"` is not recommended in general coding practice, but it works
+ To compile and then run a c file (called `test.c`)
  + `gcc test.c -o test`
  + `.\test`
+ Concerns about size of the seed as bytes of 0 are appended to the original baseseed multiple times (allocation and reallocation of memory)
+ Example of using `sha256.c` function
```
BYTE text1[] = {"abc"};      //message to be hashed
BYTE buf[SHA256_BLOCK_SIZE]; //location for hashed bytes
SHA256_CTX ctx;              //initialize SHA256_CTX object
sha256_init(&ctx);
sha256_update(&ctx, text1, strlen(text1));
sha256_final(&ctx, buf)

//Now the hashed 256 bits (represented in BYTES) are at location buf
//ie if you want to get the 2nd byte (the 8-15 bits): buf[1]
```
