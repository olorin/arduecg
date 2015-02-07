#include <avr/io.h>
#include <SD.h>
#include <Arduino.h>

#include "bits.h"
#include "session.h"
#include "frame.h"

#define SD_CHIPSELECT 4
#define SAMPLE_RATE 256

uint8_t frame_buf[FRAME_SIZE];
uint8_t frame_counter;

int init_sd() 
{
	if (!SD.begin(SD_CHIPSELECT)) {
		return -1;
	}
	return 0;
}

int init_ecg()
{
	frame_counter = 0;
	memset(frame_buf, 0, FRAME_SIZE);
	if (init_sd() < 0) {
		return -1;
	}
	uint64_t init_time = 1423297511ULL; // XXX: actually get time
	session *s = session_init(init_time, FRAME_CHANNELS);
	if (s == NULL) {
		return -2;
	}
	return 0;
}

int main(void) 
{
	if (init_ecg() != 0) {
		return -1;
	}
	for (;;) {
		frame_buf[0] = frame_counter;
		// Counter will overflow at 256.
		frame_counter++;
	}
}
