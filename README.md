# Atmega328p--Digital-clock

## Purpose of this project- 
The only purpose of this project is to try out the theory knowledge practically. It is not practical to use atmega328p to make a Digital-clock because this mcu is capable of doing much more powerful things.

### General Description-
It's a Digital-clock, can be connected via Bluetooth to mobile phone for updating time, setting alarm, update buzzer volume, update buzzer tune, set brightness, set time format, go to sleep mode, etc. all this can be done via our phone- Bluetooth text based app. and all this can be done using on board buttons too. It can live up to 48 hours depending on usage and brightness.

### Technical Description-
It has three layers:
1)`ui layer` - 
The clock usages 'tm1637' display which use custom i2c protocol.
and there is a buzzer for alarm and a photo resistor to control brightness automatically.
The clock has 7 button inputs connected via PCINT to mcu(atmega328p) only three wires are connected to PCINT pins, this was possible using 11 diods which are below the display unit, and the rest of the working is done through code in-`buttonINT.c`.
2)`backend layer` -
For time measurement and every other function it uses 'atmega328p' mcu.
3)`power supply layer` -
For power it uses 3.7v 18650 li-on cell, and to provide needed voltage to mcu it uses a boost convertor circuit which is set at 4.9v .
to charge the battery it uses a 18650 charging circuit with micro-usb port which will not let battery to overcharge or overdischarge.

### images
![20231013_005245](https://github.com/gityssh/Atmega328p--Digital-clock/assets/49648562/bc2b16e6-d884-46f2-b271-c029c6b92f49)
![Screenshot_20231014_153704_Instagram](https://github.com/gityssh/Atmega328p--Digital-clock/assets/49648562/b61bb844-8b13-4156-b837-75e31fca17ad)
![Screenshot_20231014_153720_Instagram](https://github.com/gityssh/Atmega328p--Digital-clock/assets/49648562/06487ef3-cd8c-4bca-a7f7-4b6a1968b6b4)

