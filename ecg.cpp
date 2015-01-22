#include <avr/io.h>
#include <SD.h>
#include <Arduino.h>

#define SD_CHIPSELECT 4

#define ECG_CHANNELS 6
#define SAMPLE_RATE 256
#define SAMPLE_SIZE 2

/* Packets are two bytes per channel plus one byte for the counter.
 * Channels have two-byte big-endian values. */
#define PACKET_SIZE (ECG_CHANNELS * SAMPLE_SIZE + 1)

uint8_t out_buf[PACKET_SIZE];
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
	memset(out_buf, 0, PACKET_SIZE);
	return init_sd(SD_CHIPSELECT);
}

int main(void) 
{
	if (init_ecg() != 0) {
		return -1;
	}
	for (;;) {
		out_buf[0] = counter;
		counter++;
	}
}
