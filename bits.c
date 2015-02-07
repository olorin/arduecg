#include <stdint.h>

#include "bits.h"

uint32_t swap_endian_32(uint32_t n)
{
	return (n & 0x000000FFU) << 24 |
               (n & 0x0000FF00U) << 8  |
	       (n & 0x00FF0000U) >> 8  |
	       (n & 0xFF000000U) >> 24; 
}
