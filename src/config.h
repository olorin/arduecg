#ifndef H_CONFIG
#define H_CONFIG

#define SAMPLE_RATE 256
#define SAMPLE_INTERVAL (1024/SAMPLE_RATE) // close enough

#define CHANNELS 1

#define PIN_SD_HW_CHIPSELECT 10
#define PIN_SD_CHIPSELECT 4
#define PIN_ERROR_LED 9

#define DEBUG 1

#define FRAME_SAMPLE_SIZE 4
#define FRAME_TIMEOFFSET_SIZE 4
#define FRAME_NUM_UNUSED 3

#define FRAME_SIZE (CHANNELS * FRAME_SAMPLE_SIZE +\
                    FRAME_TIMEOFFSET_SIZE +\
                    FRAME_NUM_UNUSED +\
                    1) // Frame counter byte.

#endif
