help:
	@echo 'Help details'
	@echo 'hex: compile hex file'
	@echo 'flash: install hex file'
	@echo 'program: compile hex and install'

hex:
	avr-gcc -Os -DF_CPU=16000000 -mmcu=atmega328p -c HexClock.c TM1637_x.c Time_x.c ButtonINT.c Buzz.c AutoB.c Bluetooth.c eeprom.c nap.c
	avr-gcc -DF_CPU=16000000 -mmcu=atmega328p -o HexClock.elf HexClock.o TM1637_x.o Time_x.o ButtonINT.o Buzz.o AutoB.o Bluetooth.o eeprom.o nap.o
	avr-objcopy -O ihex HexClock.elf HexClock.hex
	rm HexClock.o
	rm TM1637_x.o
	rm Time_x.o
	rm ButtonINT.o
	rm Buzz.o
	rm AutoB.o
	rm Bluetooth.o
	rm eeprom.o
	rm nap.o
	rm HexClock.elf


flash:
	avrdude -c arduino -p atmega328p -P /dev/ttyUSB0 -U flash:w:HexClock.hex

