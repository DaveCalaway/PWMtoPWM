EESchema Schematic File Version 2
LIBS:power
LIBS:device
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
LIBS:ArduProMiniTKB
LIBS:pwmTOpwm-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Pwm to Pwm"
Date ""
Rev "0.1"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 "DaveCalaway"
$EndDescr
$Comp
L ARDUPROMINI-6 uP1
U 1 1 5B33EFD1
P 6300 1500
F 0 "uP1" H 5700 -800 60  0000 C CNN
F 1 "ARDUPROMINI-6" H 5700 600 60  0000 C CNN
F 2 "ArduProMiniTKB:ArduProMini-6" H 6300 1500 60  0001 C CNN
F 3 "" H 6300 1500 60  0000 C CNN
	1    6300 1500
	1    0    0    -1  
$EndComp
$Comp
L Rotary_Encoder_Switch SW1
U 1 1 5B33F03A
P 5700 4250
F 0 "SW1" H 5700 4510 50  0000 C CNN
F 1 "Rotary_Encoder_Switch" H 5700 3990 50  0000 C CNN
F 2 "Buttons_Switches_THT:KSA_Tactile_SPST" H 5600 4410 50  0001 C CNN
F 3 "" H 5700 4510 50  0001 C CNN
	1    5700 4250
	1    0    0    -1  
$EndComp
Wire Wire Line
	6300 3200 6600 3200
Text Label 6600 3200 0    60   ~ 0
pwm_in
Wire Wire Line
	5100 3400 4600 3400
Text Label 4600 3400 0    60   ~ 0
pwm_out
Wire Wire Line
	5100 3200 4600 3200
Text Label 4600 3300 0    60   ~ 0
SDA
Wire Wire Line
	6000 4150 6350 4150
Text Label 6350 4150 0    60   ~ 0
button
Wire Wire Line
	6000 4350 6350 4350
Wire Wire Line
	6350 4350 6350 4450
$Comp
L GND #PWR01
U 1 1 5B33F11C
P 6350 4450
F 0 "#PWR01" H 6350 4200 50  0001 C CNN
F 1 "GND" H 6350 4300 50  0000 C CNN
F 2 "" H 6350 4450 50  0001 C CNN
F 3 "" H 6350 4450 50  0001 C CNN
	1    6350 4450
	1    0    0    -1  
$EndComp
Wire Wire Line
	5400 4150 5050 4150
Wire Wire Line
	5400 4350 5050 4350
Wire Wire Line
	4200 3100 5100 3100
Wire Wire Line
	4600 3000 5100 3000
Text Label 4600 3000 0    60   ~ 0
A
Text Label 5050 4150 0    60   ~ 0
A
Text Label 5050 4350 0    60   ~ 0
B
Text Label 4200 3100 0    60   ~ 0
B
Wire Wire Line
	5400 4250 4850 4250
Wire Wire Line
	4850 4250 4850 4450
$Comp
L GND #PWR02
U 1 1 5B33F1EA
P 4850 4450
F 0 "#PWR02" H 4850 4200 50  0001 C CNN
F 1 "GND" H 4850 4300 50  0000 C CNN
F 2 "" H 4850 4450 50  0001 C CNN
F 3 "" H 4850 4450 50  0001 C CNN
	1    4850 4450
	1    0    0    -1  
$EndComp
Wire Wire Line
	5100 3300 4600 3300
Text Label 4600 3200 0    60   ~ 0
SCL
Wire Wire Line
	5100 3500 4600 3500
Text Label 4600 3500 0    60   ~ 0
button
$Comp
L R R2
U 1 1 5B33F3E1
P 4750 2750
F 0 "R2" V 4830 2750 50  0000 C CNN
F 1 "10k" V 4750 2750 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 4680 2750 50  0001 C CNN
F 3 "" H 4750 2750 50  0001 C CNN
	1    4750 2750
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 5B33F495
P 4400 2750
F 0 "R1" V 4480 2750 50  0000 C CNN
F 1 "10k" V 4400 2750 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 4330 2750 50  0001 C CNN
F 3 "" H 4400 2750 50  0001 C CNN
	1    4400 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	4400 2900 4400 3100
Connection ~ 4400 3100
Wire Wire Line
	4750 2900 4750 3000
Connection ~ 4750 3000
Wire Wire Line
	4750 2200 4750 2600
Wire Wire Line
	4400 2200 4750 2200
Wire Wire Line
	4650 2200 4650 2100
Connection ~ 4650 2200
Wire Wire Line
	6300 2900 6600 2900
Text Label 6600 2600 0    60   ~ 0
Vin
Wire Wire Line
	6300 2600 6600 2600
Text Label 6600 2900 0    60   ~ 0
VCC
Wire Wire Line
	6300 2700 7100 2700
Wire Wire Line
	7100 2700 7100 2800
$Comp
L GND #PWR03
U 1 1 5B33F9DF
P 7100 2800
F 0 "#PWR03" H 7100 2550 50  0001 C CNN
F 1 "GND" H 7100 2650 50  0000 C CNN
F 2 "" H 7100 2800 50  0001 C CNN
F 3 "" H 7100 2800 50  0001 C CNN
	1    7100 2800
	1    0    0    -1  
$EndComp
$Comp
L Conn_01x04 J1
U 1 1 5B33FB86
P 7600 4250
F 0 "J1" H 7600 4450 50  0000 C CNN
F 1 "Conn_01x04" H 7600 3950 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x04_Pitch2.54mm" H 7600 4250 50  0001 C CNN
F 3 "" H 7600 4250 50  0001 C CNN
	1    7600 4250
	1    0    0    -1  
$EndComp
Wire Wire Line
	7400 4150 7000 4150
Wire Wire Line
	7400 4250 7000 4250
Wire Wire Line
	7400 4350 7000 4350
Wire Wire Line
	7400 4450 7000 4450
Text Label 7000 4150 0    60   ~ 0
GND
Text Label 7000 4250 0    60   ~ 0
VCC
Text Label 7000 4350 0    60   ~ 0
SCL
Text Label 7000 4450 0    60   ~ 0
SDA
NoConn ~ 5100 2600
NoConn ~ 5100 2700
NoConn ~ 5100 2800
NoConn ~ 5100 3600
NoConn ~ 5100 3700
NoConn ~ 6300 2800
NoConn ~ 6300 3000
NoConn ~ 6300 3100
NoConn ~ 6300 3300
NoConn ~ 6300 3400
NoConn ~ 6300 3500
NoConn ~ 6300 3600
NoConn ~ 6300 3700
$Comp
L Screw_Terminal_01x04 J2
U 1 1 5B33FFA0
P 4250 4250
F 0 "J2" H 4250 4450 50  0000 C CNN
F 1 "Screw_Terminal_01x04" H 4250 3950 50  0000 C CNN
F 2 "TerminalBlocks_Phoenix:TerminalBlock_Phoenix_MPT-2.54mm_4pol" H 4250 4250 50  0001 C CNN
F 3 "" H 4250 4250 50  0001 C CNN
	1    4250 4250
	1    0    0    -1  
$EndComp
Wire Wire Line
	4050 4150 3650 4150
Wire Wire Line
	4050 4250 3650 4250
Wire Wire Line
	4050 4350 3650 4350
Wire Wire Line
	4050 4450 3650 4450
Text Label 3650 4150 0    60   ~ 0
GND
Text Label 3650 4250 0    60   ~ 0
Vin
Text Label 3650 4350 0    60   ~ 0
pwm_in
Text Label 3650 4450 0    60   ~ 0
pwm_out
Text Label 4650 2100 0    60   ~ 0
VCC
Wire Wire Line
	4400 2600 4400 2200
Wire Wire Line
	5100 2900 4900 2900
Text Label 4900 2900 0    60   ~ 0
GND
$EndSCHEMATC
