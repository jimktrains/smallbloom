#ifndef __LIBSMALLBLOOM_H_
#define __LIBSMALLBLOOM_H_

#include <stddef.h>
#include <stdint.h>

uint8_t *bfilter;

#define FILTER_LENGTH_BYTES 14
/* Should be a prime
 *   2      3      5      7     11     13     17     19     23     29
 *  31     37     41     43     47     53     59     61     67     71
 *  73     79     83     89     97    101    103    107    109    113
 * 127    131    137    139    149    151    157    163    167    173
 * 179    181    191    193    197    199    211    223    227    229
 * 233    239    241    251
 */
#define FILTER_LENGTH_BITS 113 //8*FILTER_LENGTH_BYTES

#define BF_ITER 4

void bfadd(uint8_t *d, size_t dlen);
uint8_t bfcheck(uint8_t *d, size_t dlen);
#endif
