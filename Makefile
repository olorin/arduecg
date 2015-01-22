MCU=atmega328p
PROGRAMMER=arduino

SOURCES=ecg.c
ARTIFACTS=ecg.out ecg.hex

ecg.hex: ecg.out
	avr-objcopy -O ihex -R .eeprom ecg.out ecg.hex

ecg.out: $(SOURCES)
	avr-gcc -DF_CPU=16000000UL -mmcu=$(MCU) -o ecg.out $(SOURCES)

upload: ecg.hex
	sudo avrdude -v -c $(PROGRAMMER) -p $(MCU) -D -U flash:w:ecg.hex:i -P $(AVR_PORT)

clean:
	rm -fv $(ARTIFACTS)

.PHONY: upload
