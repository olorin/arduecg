#ifndef H_SESSION
#define H_SESSION

#include <SPI.h>
#include <SD.h>

#define SESSION_HEADER_SIZE 16

// A session lasts from when the device is powered on to when it is
// powered off, or until the frame timer has reached its maximum value
// (2^32-1 milliseconds, just under 50 days).
typedef struct {
	// Session output file.
	File fh;
	// Time of session start.
	uint64_t init_time;
	// Time delta (from init_time) of most recent frame.
	uint32_t frame_time;
	// Written out in hex as the 3-character session filename
	// suffix.
	int next_suffix;
	uint8_t counter;
} session;

session* session_init(uint64_t timestamp, uint16_t chans);

int session_write_frame(session *s, uint8_t *data, uint32_t delta_t);

void session_close(session *s);
#endif
