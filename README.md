This repository contains code for a datalogger based on the [Olimex
SHIELD-EKG-EMG](https://www.olimex.com/Products/Duino/Shields/SHIELD-EKG-EMG/)
shield on an Arduino-compatible atmega324 board.

Work in progress, doesn't do much yet.

# Building

```sh
make
AVR_PORT=/path/to/your/device upload
```

The included Makefile has been tested on Arch Linux and OpenBSD 5.6;
it'll probably work on OS X and is unlikely to do so without
modification on Windows.

## Dependencies

 - avr-binutils
 - avr-gcc
 - avr-libc
 - avrdude
