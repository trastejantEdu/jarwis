EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:switches
LIBS:relays
LIBS:motors
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:ESP8266
LIBS:dht12
LIBS:ws2812
LIBS:sonda_humedad
LIBS:fs1000a
LIBS:Garden_Guardian-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 2
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
L LM358 U202
U 1 1 5B652034
P 5550 3675
F 0 "U202" H 5550 3875 50  0000 L CNN
F 1 "LM358" H 5550 3475 50  0000 L CNN
F 2 "Housings_DIP:DIP-8_W7.62mm_LongPads" H 5550 3675 50  0001 C CNN
F 3 "" H 5550 3675 50  0001 C CNN
	1    5550 3675
	1    0    0    -1  
$EndComp
Wire Wire Line
	5850 3675 6175 3675
Text HLabel 6175 3675 2    60   Input ~ 0
OUT
$Comp
L VCC #PWR021
U 1 1 5B6520B0
P 5450 3375
F 0 "#PWR021" H 5450 3225 50  0001 C CNN
F 1 "VCC" H 5450 3525 50  0000 C CNN
F 2 "" H 5450 3375 50  0001 C CNN
F 3 "" H 5450 3375 50  0001 C CNN
	1    5450 3375
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR022
U 1 1 5B6520C6
P 5450 3975
F 0 "#PWR022" H 5450 3725 50  0001 C CNN
F 1 "GND" H 5450 3825 50  0000 C CNN
F 2 "" H 5450 3975 50  0001 C CNN
F 3 "" H 5450 3975 50  0001 C CNN
	1    5450 3975
	1    0    0    -1  
$EndComp
$Comp
L R R204
U 1 1 5B6520DC
P 5025 4175
F 0 "R204" V 5105 4175 50  0000 C CNN
F 1 "R" V 5025 4175 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 4955 4175 50  0001 C CNN
F 3 "" H 5025 4175 50  0001 C CNN
	1    5025 4175
	1    0    0    -1  
$EndComp
$Comp
L R R203
U 1 1 5B652117
P 5025 3325
F 0 "R203" V 5105 3325 50  0000 C CNN
F 1 "R" V 5025 3325 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 4955 3325 50  0001 C CNN
F 3 "" H 5025 3325 50  0001 C CNN
	1    5025 3325
	1    0    0    -1  
$EndComp
Wire Wire Line
	4875 3575 5250 3575
Wire Wire Line
	5025 3575 5025 3475
Wire Wire Line
	5025 3175 5950 3175
Wire Wire Line
	5950 3175 5950 3675
Connection ~ 5950 3675
Wire Wire Line
	4875 3775 5250 3775
Wire Wire Line
	5025 3775 5025 4025
$Comp
L GND #PWR023
U 1 1 5B652155
P 5025 4325
F 0 "#PWR023" H 5025 4075 50  0001 C CNN
F 1 "GND" H 5025 4175 50  0000 C CNN
F 2 "" H 5025 4325 50  0001 C CNN
F 3 "" H 5025 4325 50  0001 C CNN
	1    5025 4325
	1    0    0    -1  
$EndComp
$Comp
L R R201
U 1 1 5B652168
P 4725 3575
F 0 "R201" V 4805 3575 50  0000 C CNN
F 1 "R" V 4725 3575 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 4655 3575 50  0001 C CNN
F 3 "" H 4725 3575 50  0001 C CNN
	1    4725 3575
	0    1    1    0   
$EndComp
$Comp
L R R202
U 1 1 5B652191
P 4725 3775
F 0 "R202" V 4805 3775 50  0000 C CNN
F 1 "R" V 4725 3775 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 4655 3775 50  0001 C CNN
F 3 "" H 4725 3775 50  0001 C CNN
	1    4725 3775
	0    1    1    0   
$EndComp
Connection ~ 5025 3775
Connection ~ 5025 3575
$Comp
L sonda_humedad U201
U 1 1 5B652259
P 3925 3175
F 0 "U201" V 3875 3425 60  0000 C CNN
F 1 "sonda_humedad" V 4325 3325 60  0000 C CNN
F 2 "sondas:sonda_humedad" H 3925 3175 60  0001 C CNN
F 3 "" H 3925 3175 60  0001 C CNN
	1    3925 3175
	1    0    0    -1  
$EndComp
Wire Wire Line
	4575 3575 4175 3575
Wire Wire Line
	4175 3575 4175 3475
Wire Wire Line
	4575 3775 4025 3775
Wire Wire Line
	4025 3775 4025 3475
$EndSCHEMATC
