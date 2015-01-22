This repository contains code for a datalogger based on the [Olimex
SHIELD-EKG-EMG](https://www.olimex.com/Products/Duino/Shields/SHIELD-EKG-EMG/)
shield on an Arduino-compatible atmega324 board.

Work in progress, doesn't do much yet.

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

 - avr-binutils
 - avr-gcc
 - avr-libc
 - avrdude
