#include "fnv.h"

uint32_t fnv_init() { return FNV_BIAS; }
uint32_t fnv_add(uint32_t hash, uint8_t val)
{
  hash = hash ^ val;
  hash = hash * FNV_PRIME;
  return hash;
}
uint32_t fnv_finalize(uint32_t hash) { return hash; }
