#include <avr/io.h>
#include <SD.h>
#include <Arduino.h>

#include "bits.h"
#include "session.h"
#include "frame.h"

#define SD_CHIPSELECT 4
#define SAMPLE_RATE 256

#define PIN_ERROR_LED 13

#define DEBUG 1

uint8_t frame_buf[FRAME_SIZE];
uint8_t frame_counter;

void state_error()
{
	#ifdef DEBUG
	Serial.println("Entering error state.");
	#endif
	pinMode(PIN_ERROR_LED, OUTPUT);
	for (;;) {
		digitalWrite(PIN_ERROR_LED, HIGH);
		delay(500);
		digitalWrite(PIN_ERROR_LED, LOW);
		delay(500);
	}
}

void state_run()
{
	for (;;) {
		// do stuff
	}
}

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
		#ifdef DEBUG
		Serial.println("Could not initialize SD card.");
		#endif
		return -1;
	}
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

int main(void) 
{
	#ifdef DEBUG
	Serial.begin(9600);
	Serial.println("ecg-datalogger initializing.");
	#endif
	if (init_ecg() != 0) {
		state_error();
	} else {
		state_run();
	}
}
