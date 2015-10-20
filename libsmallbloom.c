#include "fnv.h"
#include "libsmallbloom.h"

void bfadd(uint8_t *d, size_t dlen)
{
  uint32_t r = fnv_init();
  uint8_t bit;
  uint8_t byte;
  for(uint8_t i = 0; i < BF_ITER; i++)
  {
    for(uint8_t j = 0; j < dlen; j++) { r = fnv_add(r, d[j]); }
    bit = fnv_finalize(r) % FILTER_LENGTH_BITS;
    // printf("%02x-%02x ", byte,bit);
    byte = bit / 8;
    bit = bit % 8;
    bfilter[byte] |= (1 << bit);
  }
}

uint8_t bfcheck(uint8_t *d, size_t dlen)
{
  uint8_t cnt = 0;
  uint32_t r = fnv_init();
  uint8_t bit;
  uint8_t byte;
  for(uint8_t i = 0; i < BF_ITER; i++)
  {
    for(uint8_t j = 0; j < dlen; j++) { r = fnv_add(r, d[j]); }
    bit = fnv_finalize(r) % FILTER_LENGTH_BITS;

    byte = bit / 8;
    bit = bit % 8;
    cnt += (bfilter[byte] & (1 << bit)) ? 1 : 0;
  }

  return cnt == BF_ITER;
}

