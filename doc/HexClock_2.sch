EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Device:Battery 3.7v
U 1 1 64576ADB
P 5300 4550
F 0 "3.7v" V 5453 4550 50  0000 C CNN
F 1 "Battery" V 5454 4550 50  0001 C CNN
F 2 "" V 5300 4610 50  0001 C CNN
F 3 "~" V 5300 4610 50  0001 C CNN
	1    5300 4550
	0    -1   -1   0   
$EndComp
$Comp
L Connector:USB_A J?
U 1 1 645782EF
P 6900 3700
F 0 "J?" H 6670 3643 50  0001 R CNN
F 1 "USB_A" H 6957 4076 50  0001 C CNN
F 2 "" H 7050 3650 50  0001 C CNN
F 3 " ~" H 7050 3650 50  0001 C CNN
	1    6900 3700
	-1   0    0    1   
$EndComp
Wire Bus Line
	6600 3600 6450 3600
Wire Bus Line
	6450 3600 6450 4550
Wire Bus Line
	6450 4550 5500 4550
Wire Bus Line
	6600 3700 6500 3700
Wire Bus Line
	6500 3700 6500 4700
Wire Bus Line
	6500 4700 5100 4700
Wire Bus Line
	5100 4700 5100 4550
$Comp
L Regulator_Switching:TPS613222ADBZ Boost_Convertor_Out-5v
U 1 1 6457B1F9
P 5300 3400
F 0 "Boost_Convertor_Out-5v" H 5300 3767 50  0000 C CNN
F 1 "TPS613222ADBZ" H 5300 3676 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 5300 2600 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tps61322.pdf" H 5300 3250 50  0001 C CNN
	1    5300 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	5300 3700 5500 3700
Wire Wire Line
	5500 3700 5500 4550
Wire Wire Line
	5700 3300 6050 3300
Wire Wire Line
	5300 3700 3950 3700
Wire Wire Line
	3950 3700 3950 3500
Wire Wire Line
	3950 3500 3700 3500
Connection ~ 5300 3700
Wire Wire Line
	4900 3300 4900 4550
Wire Wire Line
	4900 4550 5100 4550
Wire Wire Line
	4800 3350 4800 3750
Wire Wire Line
	4800 3750 6050 3750
Wire Wire Line
	6050 3750 6050 3300
Wire Wire Line
	3700 3350 4800 3350
Wire Wire Line
	3700 3200 4650 3200
Wire Wire Line
	4650 3200 4650 2850
Wire Wire Line
	6200 2850 6200 2750
Wire Wire Line
	4650 2850 6200 2850
Wire Wire Line
	3700 3050 4550 3050
Wire Wire Line
	4550 3050 4550 2800
Wire Wire Line
	4550 2800 6100 2800
Wire Wire Line
	6100 2800 6100 2750
Wire Wire Line
	6200 2850 6750 2850
Wire Wire Line
	6750 2850 6750 2750
Connection ~ 6200 2850
Wire Wire Line
	6100 2800 6650 2800
Wire Wire Line
	6650 2800 6650 2750
Connection ~ 6100 2800
Wire Bus Line
	3700 3500 3700 4850
Wire Bus Line
	3700 4850 7450 4850
Wire Bus Line
	3700 3350 3700 3450
Wire Bus Line
	3700 3450 3850 3450
Wire Bus Line
	3850 3450 3850 4800
Wire Bus Line
	3850 4800 7400 4800
Wire Bus Line
	6850 2750 6850 2900
Wire Bus Line
	6850 2900 7400 2900
Connection ~ 7400 2900
Wire Bus Line
	7400 2900 7400 2750
Wire Bus Line
	6900 2750 6900 2850
Wire Bus Line
	6900 2850 7450 2850
Connection ~ 7450 2850
Wire Bus Line
	7450 2850 7450 2700
Text GLabel 6350 2650 0    50   Input ~ 0
UART_RS232
Text GLabel 6950 2650 0    50   Input ~ 0
Bluetooth
Text GLabel 3500 2900 0    50   Input ~ 0
RX
Text GLabel 3500 3050 0    50   Input ~ 0
TX
Text GLabel 3500 3350 0    50   Input ~ 0
VCC-5V
Text GLabel 3500 3500 0    50   Input ~ 0
GND
Wire Wire Line
	3700 2900 4500 2900
Wire Wire Line
	4500 2900 4500 2750
Wire Wire Line
	4500 2750 6000 2750
Text GLabel 3550 3200 0    50   Input ~ 0
DTR
Wire Bus Line
	7400 2900 7400 4800
Wire Bus Line
	7450 2850 7450 4850
$EndSCHEMATC
