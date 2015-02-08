#include <SPI.h>

#include "bits.h"
#include "frame.h"
#include "config.h"

void read_samples(uint8_t *buf) {
	int ch;
	uint32_t v;
	for (ch = 0; ch < FRAME_CHANNELS; ch++) {
		// XXX: make this endianness-agnostic
		v = swap_endian_32(analogRead(ch));
		memcpy(buf+(4*ch), &v, 4);
	}
	#ifdef DEBUG
	Serial.print("Read samples from ADC: ");
	for (ch = 0; ch < FRAME_CHANNELS; ch++) {
		Serial.print(buf[ch*4], HEX);
		Serial.print(buf[ch*4+1], HEX);
		Serial.print(buf[ch*4+2], HEX);
		Serial.print(buf[ch*4+3], HEX);
	}
	Serial.println("");
	#endif
}
