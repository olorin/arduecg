#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <SPI.h>
#include <SD.h>

#include "session.h"
#include "bits.h"

#include "config.h"

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

// Given a *char of length at least 11, get_fname stores a string of the
// form "ecgses.XXX", where XXX is a hexadecimal integer between 0x0 and
// 0xfff. If no such unused filename exists -1 will be returned,
// otherwise the value of the integer used for the suffix plus one
// (assuming contiguity of session files, this is likely to be valid for
// the next one).
int get_fname(char *fname, int base_suffix)
{
	int suf = base_suffix;
	strncpy(fname, "ecgses.XXX", 10);
	fname[10] = '\0';
	char valid = 0;
	while (!valid && suf < 0x1000) {
		snprintf(fname+7, 4, "%3x", suf);
		if (!SD.exists(fname)) {
			valid = 1;
		}
		suf++;
	}
	return (valid ? suf : -1);
}

session* session_init(uint64_t timestamp, uint16_t channels)
{
	session *s = (session*) malloc(sizeof(session));
	if (s == NULL) {
		return NULL;
	}
	uint8_t buf[SESSION_HEADER_SIZE];
	init_session_header(buf, timestamp, channels);
	char fname[11];
	int next_suffix = get_fname(fname, 0);
	if (next_suffix < 0) {
		#ifdef DEBUG
		Serial.println("Could not find an unused filename.")
		Serial.println("Is the SD card full?")
		#endif
		free(s);
		return NULL;
	}
	s->next_suffix = next_suffix;
	s->init_time = timestamp;
	s->fh = SD.open(fname, FILE_WRITE);
	if (!s->fh) {
		#ifdef DEBUG
		Serial.print("Could not open file ");
		Serial.print(fname);
		Serial.print(" for writing.");
		#endif
		free(s);
		return NULL;
	}
	session_write(s, buf, SESSION_HEADER_SIZE);
	return s;
}

void session_close(session *s)
{
	s->fh.close();
}
