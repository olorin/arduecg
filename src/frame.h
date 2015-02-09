#include <stdint.h>

#include "config.h"

#define FRAME_SAMPLE_SIZE 4
#define FRAME_TIMEOFFSET_SIZE 4
#define FRAME_NUM_UNUSED 3

#define FRAME_SIZE (CHANNELS * FRAME_SAMPLE_SIZE +\
                    FRAME_TIMEOFFSET_SIZE +\
                    FRAME_NUM_UNUSED)
