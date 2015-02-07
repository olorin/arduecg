#include <avr/io.h>
#include <SD.h>
#include <Arduino.h>

#include "bits.h"
#include "session.h"
#include "frame.h"

#define SD_CHIPSELECT 4
#define SAMPLE_RATE 256

uint8_t out_buf[FRAME_SIZE];
uint8_t counter;

int init_sd(int chipselect) 
{
	if (!SD.begin(chipselect)) {
		return -1;
	}
	return 0;
}

int init_ecg()
{
	counter = 0;
	memset(out_buf, 0, FRAME_SIZE);
	return init_sd(SD_CHIPSELECT);
}

int main(void) 
{
	if (init_ecg() != 0) {
		return -1;
	}
	for (;;) {
		out_buf[0] = counter;
		// Counter will overflow at 256.
		counter++;
	}
}
