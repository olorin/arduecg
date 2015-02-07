#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <SPI.h>
#include <SD.h>

#include "session.h"
#include "bits.h"

void init_session_header(uint8_t* buf, uint64_t timestamp, uint16_t channels)
{
	buf[0] = 0xec; // Magic #1.
	buf[1] = 0x09; // Magic #2.
	buf[2] = 0x00; // Format epoch.
	buf[3] = 0x00; // Unused 1.
	buf[4] = 0x00; // Unused 2.
	buf[5] = 0x00; // Unused 3.
	uint16_t be_channels = swap_endian_16(channels);
	memcpy(&(buf[6]), &be_channels, 2);
	// Last eight bytes are for the timestamp.
	// XXX: this assumes we're compiled little-endian. Better to make it
	//      endianness-agnostic.
	uint64_t be_ts = swap_endian_64(timestamp);
	memcpy(&(buf[8]), &be_ts, 8);
}

int session_write(session *s, uint8_t *buf, size_t len)
{
	int written = s->fh.write(buf, len);
	s->fh.flush();
	return written;
}

session* init_session(uint64_t timestamp, uint16_t channels)
{
	session *s = (session*) malloc(sizeof(session));
	if (s == NULL) {
		return NULL;
	}
	uint8_t buf[SESSION_HEADER_SIZE];
	init_session_header(buf, timestamp, channels);
	char fname[33];
	strncpy(fname, "ecg/session_", 12);
	snprintf(fname+12, 21, "%llu", timestamp);
	s->init_time = timestamp;
	s->fh = SD.open(fname, FILE_WRITE);
	if (!s->fh) {
		return NULL;
	}
	session_write(s, buf, SESSION_HEADER_SIZE);
	return s;
}
