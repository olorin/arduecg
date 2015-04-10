/* Constants for hardware and data format. If you're looking for
 * compile-time configuration options, see config.h. */

#ifndef H_CONSTANTS
#define H_CONSTANTS

#include "config.h"

#define SAMPLE_INTERVAL (1024/SAMPLE_RATE) // close enough

#define PIN_SD_HW_CHIPSELECT 10
#define PIN_SD_CHIPSELECT 4
#define PIN_ERROR_LED 9

#define FRAME_SAMPLE_SIZE 4
#define FRAME_TIMEOFFSET_SIZE 4
#define FRAME_NUM_UNUSED 3

#define FRAME_SIZE (CHANNELS * FRAME_SAMPLE_SIZE +\
                    FRAME_TIMEOFFSET_SIZE +\
                    FRAME_NUM_UNUSED +\
                    1) // Frame counter byte.

#endif
