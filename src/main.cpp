#include <avr/io.h>
#include <SD.h>
#include <Arduino.h>

#include "bits.h"
#include "session.h"
#include "frame.h"

#define SAMPLE_RATE 256

#define PIN_SD_HW_CHIPSELECT 10
#define PIN_SD_CHIPSELECT 10
#define PIN_ERROR_LED 13

#define DEBUG 1

uint8_t frame_buf[FRAME_SIZE];
uint8_t frame_counter;

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
	#ifdef DEBUG
	Serial.println("In run state.");
	delay(100);
	#endif
}

int init_ecg()
{
	frame_counter = 0;
	memset(frame_buf, 0, FRAME_SIZE);
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
	session *s = session_init(init_time, FRAME_CHANNELS);
	if (s == NULL) {
		#ifdef DEBUG
		Serial.println("Could not initialize session.");
		#endif
		return -2;
	}
	return 0;
}

void setup(void) 
{
	pinMode(PIN_ERROR_LED, OUTPUT);
	pinMode(PIN_SD_HW_CHIPSELECT, OUTPUT);
	#ifdef DEBUG
	Serial.begin(9600);
	Serial.println("ecg-datalogger initializing.");
	#endif
	if (init_ecg() != 0) {
		state_error();
	}
}

void loop(void) {
	state_run();
}
