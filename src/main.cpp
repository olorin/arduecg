#include <avr/io.h>
#include <SD.h>
#include <Arduino.h>

#include "bits.h"
#include "session.h"
#include "timer.h"
#include "config.h"

session *sess;
volatile uint8_t isr_lock;

// This will take at least 100*CHANNELS microseconds.
void read_samples() {
	if (isr_lock) {
		#ifdef DEBUG
		Serial.println("Hit ISR lock - timing is wrong, try lowering sample rate.");
		#endif
		return;
	}
	isr_lock = 1;

	int ch;
	uint32_t smpl;
	uint8_t ecg_samples[CHANNELS * FRAME_SAMPLE_SIZE];

	for (ch = 0; ch < CHANNELS; ch++) {
		// XXX: make this endianness-agnostic
		smpl = swap_endian_32(analogRead(ch));
		memcpy((void*)(ecg_samples + (4*ch)), &smpl, 4);
	}
	// XXX: millis() will be behind real time due to time spent in
	//      the ISR; use the RTC instead.
	uint32_t dt = swap_endian_32(millis());
	if (session_write_frame(sess, (uint8_t*) ecg_samples, dt) != 0) {
		#ifdef DEBUG
		Serial.println("Error writing frame.");
		#endif
	}
	/*
	#ifdef DEBUG
	Serial.println("Read samples from ADC.");
	for (ch = 0; ch < CHANNELS; ch++) {
		Serial.print(ecg_samples[ch*4], HEX);
		Serial.print(ecg_samples[ch*4+1], HEX);
		Serial.print(ecg_samples[ch*4+2], HEX);
		Serial.print(ecg_samples[ch*4+3], HEX);
	}
	Serial.println("");
	#endif
	*/
	isr_lock = 0;
}

int init_datalogger()
{
	isr_lock = 0;
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
	sess = session_init(init_time, CHANNELS, SAMPLE_RATE);
	if (sess == NULL) {
		#ifdef DEBUG
		Serial.println("Could not initialize session.");
		#endif
		return -2;
	}
	delay(500);
	#ifdef DEBUG
	Serial.println("Enabling interrupt timer.");
	#endif
	timer_init(SAMPLE_INTERVAL, read_samples);
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
	// Everything done inside the read_samples ISR.
}
