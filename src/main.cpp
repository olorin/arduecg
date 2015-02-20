#include <avr/io.h>
#include <SD.h>
#include <Arduino.h>

#include "bits.h"
#include "session.h"
#include "timer.h"
#include "config.h"

session *sess;
volatile uint8_t ecg_samples[CHANNELS * FRAME_SAMPLE_SIZE];
volatile uint8_t samples_waiting;

// This will take at least 100*CHANNELS microseconds.
void read_samples() {
	int ch;
	uint32_t v;
	uint8_t *sample_buf;

	for (ch = 0; ch < CHANNELS; ch++) {
		// XXX: make this endianness-agnostic
		v = swap_endian_32(analogRead(ch));
		sample_buf = ((uint8_t*)ecg_samples) + (4*ch);
		memcpy(sample_buf, &v, 4);
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
	samples_waiting = 1;
}

int init_datalogger()
{
	samples_waiting = 0;
	timer_init(SAMPLE_INTERVAL, read_samples);
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
	timer_start();
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

// This must take <4ms; make sure this is actually the case, or drop the
// sample rate.
void state_run()
{
	if (!samples_waiting) {
		return;
	}
	samples_waiting = 0;
	// XXX: millis() will be behind real time due to time spent in
	//      the ISR; use the RTC instead.
	uint32_t dt = swap_endian_32(millis());
	session_write_frame(sess, (uint8_t*) ecg_samples, dt);
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
