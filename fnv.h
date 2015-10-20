#ifndef __LIBSMALLBLOOM_FNV_H__
#define __LIBSMALLBLOOM_FNV_H__

#include <stdint.h>

#define FNV_PRIME 16777619
#define FNV_BIAS 2166136261

uint32_t fnv_init();
uint32_t fnv_add(uint32_t hash, uint8_t val);
uint32_t fnv_finalize(uint32_t hash);
#endif
