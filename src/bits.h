#ifndef H_ECG_BITS
#define H_ECG_BITS

#include <stdint.h>

// Functions to manipulate endianness.

uint16_t swap_endian_16(uint16_t n);

uint32_t swap_endian_32(uint32_t n);

uint64_t swap_endian_64(uint64_t n);

#endif
