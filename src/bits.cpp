#include <stdint.h>

#include "bits.h"

uint16_t swap_endian_16(uint16_t n)
{
	return (n & 0x00FFU) << 8 |
	       (n & 0xFF00U) >> 8;
}

uint32_t swap_endian_32(uint32_t n)
{
	return (n & 0x000000FFU) << 24 |
	       (n & 0x0000FF00U) << 8  |
	       (n & 0x00FF0000U) >> 8  |
	       (n & 0xFF000000U) >> 24; 
}

uint64_t swap_endian_64(uint64_t n)
{
	return (n & 0x00000000000000FFUL) << 56 |
	       (n & 0x000000000000FF00UL) << 40 |
	       (n & 0x0000000000FF0000UL) << 24 |
	       (n & 0x00000000FF000000UL) << 8  |
	       (n & 0x000000FF00000000UL) >> 8  |
	       (n & 0x0000FF0000000000UL) >> 24 |
	       (n & 0x00FF000000000000UL) >> 40 |
	       (n & 0xFF00000000000000UL) >> 56;
}
