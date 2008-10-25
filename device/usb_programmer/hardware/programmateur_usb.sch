EESchema Schematic File Version 1
LIBS:power,./components,device,conn,linear,regul,74xx,cmos4000,adc-dac,memory,xilinx,special,microcontrollers,dsp,microchip,analog_switches,motorola,texas,intel,audio,interface,digital-audio,philips,display,cypress,siliconi,contrib,valves,./programmateur_usb.cache
EELAYER 23  0
EELAYER END
$Descr A4 11700 8267
Sheet 1 2
Title ""
Date "25 oct 2008"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Kmarq B 2000 1450 "Warning Pin BiDi Non connectée" F=1
Kmarq B 2000 1600 "Warning Pin BiDi Non connectée" F=1
Connection ~ 2800 1700
Wire Wire Line
	2800 1700 2800 1800
Wire Wire Line
	2800 1800 2000 1800
Wire Wire Line
	2000 1800 2000 1700
Connection ~ 2750 1700
Wire Wire Line
	2750 1600 2750 1700
Wire Wire Line
	2750 1450 3450 1450
Wire Wire Line
	2750 1700 3450 1700
Wire Wire Line
	5100 1800 5100 1700
Wire Wire Line
	5100 1700 4900 1700
$Comp
L GND #PWR01
U 1 1 49030E4F
P 5100 1800
F 0 "#PWR01" H 5100 1800 30  0001 C C
F 1 "GND" H 5100 1730 30  0001 C C
	1    5100 1800
	1    0    0    -1  
$EndComp
$Comp
L USB J1
U 1 1 49030DF3
P 2350 1250
F 0 "J1" H 2300 1650 60  0000 C C
F 1 "USB" V 2100 1400 60  0000 C C
	1    2350 1250
	-1   0    0    -1  
$EndComp
$Sheet
S 3450 1300 1450 550 
F0 "power_supply" 60
F1 "power_supply.sch" 60
F2 "GND" U R 4900 1700 60 
F3 "+5V" O R 4900 1400 60 
F4 "+12V" O R 4900 1550 60 
F5 "USB_GND" U L 3450 1700 60 
F6 "USB_5V" I L 3450 1450 60 
$EndSheet
$EndSCHEMATC
