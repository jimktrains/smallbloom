#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

uint8_t *filter;


/* RS Galois Field 
 * x^8 + x^4 + x^3 + x^2 + 1
 */
#define LFSR(c) ((( (c) << 1) ^ (((c) & 0x80) ? 0x1d : 0)) % 256)
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

void add(uint8_t *d, size_t dlen)
{
  uint8_t r = 0;
  uint8_t bit;
  uint8_t byte;
  for(uint8_t i = 0; i < BF_ITER; i++)
  {
    for(uint8_t j = 0; j < dlen; j++)
      r = LFSR(r ^ d[i]);
    bit = r % FILTER_LENGTH_BITS;
    //printf("%02x-%02x ", byte,bit);
    byte = bit / 8;
    bit = bit % 8;
    filter[byte] |= (1 << bit);
  }
}

uint8_t check(uint8_t *d, size_t dlen)
{
  uint8_t cnt = 0;
  uint8_t r = 0;
  uint8_t bit;
  uint8_t byte;
  for(uint8_t i = 0; i < BF_ITER; i++)
  {
    for(uint8_t j = 0; j < dlen; j++)
      r = LFSR(r ^ d[i]);
    bit = r % FILTER_LENGTH_BITS;
    byte = bit / 8;
    bit = bit % 8;
    cnt += (filter[byte] & (1 << bit)) ? 1 : 0;
  }

  return cnt == BF_ITER;
}


void print_did(uint8_t *d)
{
  for(uint8_t i = 0 ; i < 5; i++)
    printf("%02x", d[i]);
}

int main()
{
  uint8_t devices[][5] = {
    {0x0c, 0x3d, 0x54, 0xd7, 0x12},
    {0x0c, 0x3d, 0x54, 0xf7, 0x54},
    {0x0c, 0x3d, 0x54, 0xee, 0x14},
    {0x0c, 0x3d, 0x54, 0xd7, 0x13},
    {0x0c, 0x3d, 0x54, 0xd7, 0x14},
    {0x0c, 0x3d, 0x54, 0xfe, 0x14},
    {0xd7, 0xb9, 0x5e, 0xbb, 0xe7},
    {0x3f, 0x39, 0xe6, 0xeb, 0xd3},
    {0x3f, 0x39, 0xe6, 0xeb, 0xde},
    {0x3f, 0x39, 0xe6, 0xeb, 0xff},
    {0x3f, 0x34, 0xe6, 0xeb, 0xdf},
    {0x3f, 0x35, 0xe6, 0xeb, 0xf3},
    {0x3f, 0x36, 0xe6, 0xeb, 0x99},
    {0x3f, 0x38, 0xe7, 0xeb, 0xd9},
    {0x3f, 0x30, 0xe0, 0xe0, 0x90},
    {0x4f, 0x39, 0x96, 0x0b, 0x80},
    {0x4f, 0x37, 0xe6, 0x6b, 0xd8},
    {0x4f, 0x69, 0xe6, 0xe6, 0x77},
    {0x4f, 0x35, 0xe6, 0x66, 0xd7},
    {0x7f, 0x49, 0xe6, 0x7b, 0x73},
    {0x6d, 0x3e, 0xef, 0xca, 0x50},
    {0xa8, 0xdf, 0xb3, 0xe1, 0x11},
    {0x9d, 0xa7, 0x75, 0x70, 0xdb},
    {0x60, 0xd3, 0xbf, 0x3a, 0xef},
    {0x80, 0xec, 0x79, 0x1f, 0x24},
    {0x1e, 0xf8, 0x45, 0x40, 0x91},
    {0xe1, 0x4a, 0xe3, 0x13, 0x89},
    {0x09, 0xe3, 0xb8, 0x3f, 0x31},
    {0x72, 0x6d, 0xa7, 0x21, 0x4f},
    {0x6d, 0x3e, 0xef, 0xaa, 0x50},
    {0xa8, 0xdf, 0xb3, 0x61, 0x51},
    {0x9d, 0xa7, 0x75, 0x72, 0x5b},
    {0x60, 0xd3, 0xbf, 0x32, 0x5f},
    {0x80, 0xec, 0x79, 0x2f, 0x54},
  };
  filter = (uint8_t *) malloc(FILTER_LENGTH_BYTES);

  uint8_t start = 16, end = 24;
  for(uint8_t i = start; i < end; i++)
  {
    printf("Adding ");
    add(devices[i], 5);
    print_did(devices[i]);
    printf(" %s\n", check(devices[i], 5) ? "YES" : "NO");
  }

  uint16_t cnt_pos = 0;
  uint16_t cnt = 0;
  uint8_t c = 0;
  for(uint8_t i = end; i < 32; i++)
  {
    for(uint8_t j = 0; j < 5; j++)
    {
      cnt++;
      c = check(devices[i]+j, 5);
      if (c == 1)
      {
        cnt_pos++;
        print_did(devices[i]+j);
        printf(" %s\n", c ? "YES" : "NO");
      }
    }
  }
  for(uint8_t i = 0; i < start; i++)
  {
    for(uint8_t j = 0; j < 5; j++)
    {
      cnt++;
      c = check(devices[i]+j, 5);
      if (c == 1)
      {
        cnt_pos++;
        print_did(devices[i]+j);
        printf(" %s\n", c ? "YES" : "NO");
      }
    }
  }
  printf("All Tested: %d\n", cnt);
  printf("False Positives: %d\n", cnt_pos);

  return 0;
}
