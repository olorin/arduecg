#include <avr/io.h>
#include <SD.h>
#include <Arduino.h>

#define ECG_CHANNELS 6
#define SAMPLE_RATE 256
#define SAMPLE_SIZE 2

/* Packets are two bytes per channel plus one byte for the counter.
 * Channels have two-byte big-endian values. */
#define PACKET_SIZE (ECG_CHANNELS * SAMPLE_SIZE + 1)

uint8_t out_buf[PACKET_SIZE];
uint8_t counter;

void init()
{
	int i;
	counter = 0;
	memset(out_buf, 0, PACKET_SIZE);
}

int main(void) 
{
	init();
	for (;;) {
		out_buf[0] = counter;
		counter++;
	}
}
