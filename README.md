This repository contains code for a datalogger based on the [Olimex
EKG-EMG shield](https://www.olimex.com/Products/Duino/Shields/SHIELD-EKG-EMG/)
on an Arduino-compatible atmega324 board.

Out of the box it should support up to four ECG channels (if you have
four EKG-EMG shields), but it's only been tested with one.

This is a work in progress; most of the functionality is present. The
only 'critical' feature yet to be implemented is the RTC code, so
session initialization times are not currently valid.

# Known issues

 - Real-time clock code not yet implemented, so session times are not
   accurate.
 - Currently assumes a little-endian compiler (avr-gcc is one by
   default).

# Hardware

 - [Olimex EKG-EMG shield](https://www.olimex.com/Products/Duino/Shields/SHIELD-EKG-EMG/)
 - atmega328p-based Arduino with a μSD slot (I'm using the [Freetronics
   EtherTen](http://www.freetronics.com.au/products/etherten); the
   Arduino Uno with an Ethernet shield should also work, but is
   untested.
 - I2C real-time clock (DS3232)
 - μSD card

# Preparation

 - Format the SD card to FAT16.

## Wiring

 - Shield fits on the board in the usual way.
 - DS3232:
  - GND to GND
  - VCC on the RTC to 5V on the shield
  - SDA on the RTC to A4 on the shield
  - SCL on the RTC to A5 on the shield

# Building

This project uses [sudar's Arduino Makefile
template](https://github.com/sudar/Arduino-Makefile); it's copied here
under `lib/ardmk`.

```sh
export MONITOR_PORT=/path/to/your/device
export ARDUINO_DIR=/path/to/arduino/application/directory
cd src
make
make upload
```

## Dependencies

No libraries beyond the Arduino standard libraries are required.

### Tools

 - avr-binutils
 - avr-gcc
 - avr-libc
 - avrdude
