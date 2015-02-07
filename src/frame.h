#include <stdint.h>

#define FRAME_CHANNELS 6
#define FRAME_SAMPLE_SIZE 4
#define FRAME_TIMEOFFSET_SIZE 4
#define FRAME_NUM_UNUSED 3

#define FRAME_SIZE (FRAME_CHANNELS * FRAME_SAMPLE_SIZE +\
                    FRAME_TIMEOFFSET_SIZE +\
                    FRAME_NUM_UNUSED)
