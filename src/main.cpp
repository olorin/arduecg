#include <avr/io.h>
#include <SD.h>
#include <Arduino.h>

#include "bits.h"
#include "session.h"
#include "config.h"

session *sess;

void read_samples(uint8_t *buf) {
	int ch;
	uint32_t v;
	for (ch = 0; ch < CHANNELS; ch++) {
		// XXX: make this endianness-agnostic
		v = swap_endian_32(analogRead(ch));
		memcpy(buf+(4*ch), &v, 4);
	}
	#ifdef DEBUG
	/*Serial.println("Read samples from ADC.");
	for (ch = 0; ch < CHANNELS; ch++) {
		Serial.print(buf[ch*4], HEX);
		Serial.print(buf[ch*4+1], HEX);
		Serial.print(buf[ch*4+2], HEX);
		Serial.print(buf[ch*4+3], HEX);
	}
	Serial.println("");*/
	#endif
}

int init_datalogger()
{
	if (!SD.begin(PIN_SD_CHIPSELECT)) {
		#ifdef DEBUG
		Serial.println("Could not initialize SD card.");
		#endif
		return -1;
	}
	#ifdef DEBUG
	Serial.println("Initializing first session.");
	#endif
	uint64_t init_time = 1423297511ULL; // XXX: actually get time
	sess = session_init(init_time, CHANNELS);
	if (sess == NULL) {
		#ifdef DEBUG
		Serial.println("Could not initialize session.");
		#endif
		return -2;
	}
	return 0;
}

void state_error()
{
	#ifdef DEBUG
	Serial.println("Entering error state.");
	#endif
	for (;;) {
		digitalWrite(PIN_ERROR_LED, HIGH);
		delay(500);
		digitalWrite(PIN_ERROR_LED, LOW);
		delay(500);
	}
}

void state_run()
{
	uint8_t buf[FRAME_SAMPLE_SIZE*CHANNELS];
	read_samples(buf);
	uint32_t dt = swap_endian_32(millis());
	session_write_frame(sess, buf, dt);
	delay(4);
}


void setup(void) 
{
	pinMode(PIN_ERROR_LED, OUTPUT);
	pinMode(PIN_SD_HW_CHIPSELECT, OUTPUT);
	#ifdef DEBUG
	Serial.begin(9600);
	Serial.println("ecg-datalogger initializing.");
	#endif
	if (init_datalogger() != 0) {
		state_error();
	}
}

void loop(void) {
	state_run();
}
