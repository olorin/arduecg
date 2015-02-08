#ifndef H_SESSION
#define H_SESSION

#include <SPI.h>
#include <SD.h>

#define SESSION_HEADER_SIZE 16

typedef struct {
	File fh;
	uint64_t init_time;
	int next_suffix;
} session;

session* session_init(uint64_t timestamp, uint16_t chans);

int session_write(session *s, uint8_t *buf, size_t len);

void session_close(session *s);
#endif
