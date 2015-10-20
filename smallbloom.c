#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "libsmallbloom.h"

#include "test_dids.h"

void print_did(uint8_t *d);

int main()
{
  bfilter = (uint8_t *) malloc(FILTER_LENGTH_BYTES);

  uint8_t device_cnt = sizeof(devices) / 5 / sizeof(uint8_t);

  // Devices [start, end)
  uint8_t start = 0, end = 11;
  for(uint8_t i = start; i < end; i++)
  {
    printf("Adding ");
    bfadd(devices[i], 5);
    print_did(devices[i]);
    printf(" %s\n", bfcheck(devices[i], 5) ? "YES" : "NO");
  }

  // Check the rest of all the devices and keep track of how many false
  // positives. This includes abusing the fact that the DIDs are all in
  // contiguous and that we can just shift over to the unaligned DIDs
  uint16_t cnt_pos = 0;
  uint16_t cnt = 0;
  uint8_t c = 0;
  for(uint8_t i = end; i < device_cnt-1; i++)
  {
    for(uint8_t j = 0; j < 5; j++)
    {
      cnt++;
      c = bfcheck(devices[i]+j, 5);
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
      c = bfcheck(devices[i]+j, 5);
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

void print_did(uint8_t *d)
{
  for(uint8_t i = 0 ; i < 5; i++)
    printf("%02x", d[i]);
}
