This repository contains code for a datalogger based on the [Olimex
EKG-EMG shield](https://www.olimex.com/Products/Duino/Shields/SHIELD-EKG-EMG/)
on an Arduino-compatible atmega324 board.

Work in progress, doesn't do much yet.

# Hardware

 - [Olimex EKG-EMG shield](https://www.olimex.com/Products/Duino/Shields/SHIELD-EKG-EMG/)
 - atmega328p-based Arduino with a μSD slot (I'm using the [Freetronics
   EtherTen](http://www.freetronics.com.au/products/etherten))
 - I2C real-time clock (DS1307 or DS3232)
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
template](https://github.com/sudar/Arduino-Makefile); it's a submodule
of this repository, so make sure it's cloned before building.

```sh
export MONITOR_PORT=/path/to/your/device
export ARDUINO_DIR=/path/to/arduino/application/directory
cd src
make
make upload
```

## Dependencies

### Tools

 - avr-binutils
 - avr-gcc
 - avr-libc
 - avrdude

### Libraries

 - [Time](https://github.com/PaulStoffregen/Time)
