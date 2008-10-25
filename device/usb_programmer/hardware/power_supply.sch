EESchema Schematic File Version 1
LIBS:power,./components,device,conn,linear,regul,74xx,cmos4000,adc-dac,memory,xilinx,special,microcontrollers,dsp,microchip,analog_switches,motorola,texas,intel,audio,interface,digital-audio,philips,display,cypress,siliconi,contrib,valves,./programmateur_usb.cache
EELAYER 23  0
EELAYER END
$Descr A4 11700 8267
Sheet 2 2
Title ""
Date "25 oct 2008"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Kmarq B 5800 2550 "Warning Pin power_in non pilotée (Net 6)" F=1
$Comp
L GND #PWR02
U 1 1 4902355D
P 6700 4400
F 0 "#PWR02" H 6700 4400 30  0001 C C
F 1 "GND" H 6700 4330 30  0001 C C
	1    6700 4400
	-1   0    0    -1  
$EndComp
Wire Wire Line
	6700 4400 6700 4200
Wire Wire Line
	6700 4200 6950 4200
$Comp
L GND #PWR03
U 1 1 49023554
P 3650 4400
F 0 "#PWR03" H 3650 4400 30  0001 C C
F 1 "GND" H 3650 4330 30  0001 C C
	1    3650 4400
	1    0    0    -1  
$EndComp
Wire Wire Line
	3650 4400 3650 4200
Wire Wire Line
	3650 4200 3400 4200
Wire Wire Line
	6800 2850 6800 2800
Wire Wire Line
	6450 4000 5600 4000
Wire Wire Line
	6450 4000 6450 3800
Wire Wire Line
	5150 2300 3400 2300
Wire Wire Line
	5950 2400 5800 2550
Wire Wire Line
	4400 3100 4400 2400
Wire Wire Line
	4400 2400 4950 2400
Wire Wire Line
	4950 2400 5100 2550
Wire Wire Line
	5800 2550 5800 2300
Wire Wire Line
	5800 2300 5750 2300
Wire Wire Line
	5450 4100 5450 3850
Wire Wire Line
	4400 3500 4400 4000
Wire Wire Line
	4400 4000 5300 4000
Wire Wire Line
	5300 4000 5450 3850
Wire Wire Line
	5450 3850 5600 4000
Wire Wire Line
	6450 3300 6300 3300
Connection ~ 5800 2550
Connection ~ 5100 2550
Wire Wire Line
	6950 2400 6350 2400
Wire Wire Line
	4650 3300 4650 4100
Wire Wire Line
	4650 5050 4650 5000
Wire Wire Line
	5100 2550 5100 2100
Wire Wire Line
	5100 2100 6950 2100
Connection ~ 5100 2300
Wire Wire Line
	6800 2400 6450 2750
Connection ~ 6800 2400
Wire Wire Line
	6450 2750 6450 2800
$Comp
L GND #PWR04
U 1 1 490233F9
P 6800 2850
F 0 "#PWR04" H 6800 2850 30  0001 C C
F 1 "GND" H 6800 2780 30  0001 C C
	1    6800 2850
	1    0    0    -1  
$EndComp
$Comp
L CAPAPOL C3
U 1 1 490233EE
P 6800 2600
F 0 "C3" H 6850 2700 50  0000 L C
F 1 "470uf" H 6850 2500 50  0000 L C
	1    6800 2600
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR05
U 1 1 4902329D
P 4650 5050
F 0 "#PWR05" H 4650 5050 30  0001 C C
F 1 "GND" H 4650 4980 30  0001 C C
	1    4650 5050
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR06
U 1 1 49022B4D
P 5450 4100
F 0 "#PWR06" H 5450 4100 30  0001 C C
F 1 "GND" H 5450 4030 30  0001 C C
	1    5450 4100
	1    0    0    -1  
$EndComp
$Comp
L LM2577 U1
U 1 1 4902300C
P 5450 3200
F 0 "U1" H 5300 3700 60  0000 C C
F 1 "LM2577" H 5450 3600 60  0000 C C
	1    5450 3200
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 49022CB0
P 4400 3300
F 0 "C1" H 4450 3400 50  0000 L C
F 1 "100nf" H 4100 3200 50  0000 L C
	1    4400 3300
	1    0    0    -1  
$EndComp
$Comp
L DIODESCH D1
U 1 1 490230E3
P 6150 2400
F 0 "D1" H 6150 2500 40  0000 C C
F 1 "1N5821" H 6150 2300 40  0000 C C
	1    6150 2400
	1    0    0    -1  
$EndComp
$Comp
L R R3
U 1 1 4902308F
P 6450 3550
F 0 "R3" V 6530 3550 50  0000 C C
F 1 "120R" V 6450 3550 50  0000 C C
	1    6450 3550
	1    0    0    -1  
$EndComp
$Comp
L INDUCTOR L1
U 1 1 49022DC7
P 5450 2300
F 0 "L1" V 5400 2300 40  0000 C C
F 1 "680uH" V 5550 2300 40  0000 C C
	1    5450 2300
	0    -1   -1   0   
$EndComp
$Comp
L CAPAPOL C2
U 1 1 49022D69
P 4650 4800
F 0 "C2" H 4700 4900 50  0000 L C
F 1 "220uf" H 4700 4700 50  0000 L C
	1    4650 4800
	1    0    0    -1  
$EndComp
Text GLabel 6950 4200 2    60   UnSpc
GND
Text GLabel 6950 2100 2    60   Output
+5V
Text GLabel 6950 2400 2    60   Output
+12V
Text GLabel 3400 4200 0    60   UnSpc
USB_GND
Text GLabel 3400 2300 0    60   Input
USB_5V
$Comp
L R R1
U 1 1 490227CB
P 4650 4350
F 0 "R1" V 4730 4350 50  0000 C C
F 1 "470" V 4650 4350 50  0000 C C
	1    4650 4350
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 490227C9
P 6450 3050
F 0 "R2" V 6530 3050 50  0000 C C
F 1 "1K05" V 6450 3050 50  0000 C C
	1    6450 3050
	1    0    0    -1  
$EndComp
$EndSCHEMATC
