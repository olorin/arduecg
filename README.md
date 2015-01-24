This repository contains code for a datalogger based on the [Olimex
EKG-EMG shield](https://www.olimex.com/Products/Duino/Shields/SHIELD-EKG-EMG/)
on an Arduino-compatible atmega324 board.

Work in progress, doesn't do much yet.

# Hardware

 - [Olimex EKG-EMG shield](https://www.olimex.com/Products/Duino/Shields/SHIELD-EKG-EMG/)
 - atmega328p-based Arduino with a μSD slot (I'm using the [Freetronics
   EtherTen](http://www.freetronics.com.au/products/etherten))
 - μSD card

# Preparation

 - Format the SD card to FAT32.

# Building

This project uses [sudar's Arduino Makefile
template](https://github.com/sudar/Arduino-Makefile); it's a submodule
of this repository, so make sure it's cloned before building.

```sh
export MONITOR_PORT=/path/to/your/device
export ARDUINO_DIR=/path/to/arduino/application/directory
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
