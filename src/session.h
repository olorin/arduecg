#ifndef H_SESSION
#define H_SESSION

#include <SPI.h>
#include <SD.h>

#define SESSION_HEADER_SIZE 16

typedef struct {
	File fh;
	uint64_t init_time;
	uint32_t frame_time;
	int next_suffix;
	uint8_t counter;
} session;

session* session_init(uint64_t timestamp, uint16_t chans);

int session_write_frame(session *s, uint8_t *data, uint32_t delta_t);

void session_close(session *s);
#endif
