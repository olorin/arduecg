#include <SPI.h>
#include <Wire.h>

#include "ds3232.h"

// Binary-coded decimal to byte.
uint8_t decodeBCD(uint8_t n)
{
	return (n >> 4) * 10 + (n & 0x0F);
}

// Byte to binary-coded decimal.
uint8_t encodeBCD(uint8_t n)
{
	return ((n / 10) << 4) + (n % 10);
}

void ds3232_init(int sda, int scl)
{
	pinMode(sda, INPUT);
	pinMode(scl, INPUT);
	Wire.begin();
}

void ds3232_read_time(uint8_t buf)
{
	Wire.beginTransmission(DS3232_I2C_ADDRESS);
	Wire.write(0x00);
	Wire.endTransmission();
	Wire.requestFrom(DS3232_I2C_ADDRESS, 7);
}
