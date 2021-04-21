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
L Transistor_BJT:BC547 Q2
U 1 1 607EEBAA
P 1850 4850
F 0 "Q2" H 2041 4896 50  0000 L CNN
F 1 "BC547" H 2041 4805 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline" H 2050 4775 50  0001 L CIN
F 3 "http://www.fairchildsemi.com/ds/BC/BC547.pdf" H 1850 4850 50  0001 L CNN
	1    1850 4850
	1    0    0    -1  
$EndComp
$Comp
L Relay:SILxx-1Axx-71x K2
U 1 1 607EF4FE
P 2350 4350
F 0 "K2" V 1783 4350 50  0000 C CNN
F 1 "SILxx-1Axx-71x" V 1874 4350 50  0000 C CNN
F 2 "Relay_THT:Relay_SPST_StandexMeder_SIL_Form1A" H 2700 4300 50  0001 L CNN
F 3 "https://standexelectronics.com/wp-content/uploads/datasheet_reed_relay_SIL.pdf" H 2350 4350 50  0001 C CNN
	1    2350 4350
	0    1    1    0   
$EndComp
Wire Wire Line
	1950 4650 1950 4550
Wire Wire Line
	1950 4550 2050 4550
$Comp
L power:GND #PWR0101
U 1 1 607F2CBD
P 1950 5050
F 0 "#PWR0101" H 1950 4800 50  0001 C CNN
F 1 "GND" H 1955 4877 50  0000 C CNN
F 2 "" H 1950 5050 50  0001 C CNN
F 3 "" H 1950 5050 50  0001 C CNN
	1    1950 5050
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0102
U 1 1 607F327D
P 2750 4450
F 0 "#PWR0102" H 2750 4300 50  0001 C CNN
F 1 "+5V" H 2765 4623 50  0000 C CNN
F 2 "" H 2750 4450 50  0001 C CNN
F 3 "" H 2750 4450 50  0001 C CNN
	1    2750 4450
	1    0    0    -1  
$EndComp
Wire Wire Line
	2650 4550 2750 4550
Wire Wire Line
	2750 4550 2750 4450
$Comp
L symbols:atxpanel J3
U 1 1 607F43C9
P 10750 1250
F 0 "J3" H 10800 1800 50  0000 R CNN
F 1 "atxpanel" H 10900 1700 50  0000 R CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_2x10_P2.54mm_Horizontal" H 10750 1250 50  0001 C CNN
F 3 "" H 10750 1250 50  0001 C CNN
	1    10750 1250
	-1   0    0    1   
$EndComp
Text GLabel 10400 1200 0    50   UnSpc ~ 0
PWRBTN_P
Text GLabel 10400 1100 0    50   UnSpc ~ 0
PWRBTN_N
Text GLabel 1950 4150 0    50   UnSpc ~ 0
PWRBTN_N
Text GLabel 2750 4150 2    50   UnSpc ~ 0
PWRBTN_P
Text GLabel 1150 4850 0    50   Input ~ 0
PWRBTN_TTL
$Comp
L Transistor_BJT:BC547 Q1
U 1 1 607F7906
P 1850 2350
F 0 "Q1" H 2041 2396 50  0000 L CNN
F 1 "BC547" H 2041 2305 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline" H 2050 2275 50  0001 L CIN
F 3 "http://www.fairchildsemi.com/ds/BC/BC547.pdf" H 1850 2350 50  0001 L CNN
	1    1850 2350
	1    0    0    -1  
$EndComp
$Comp
L Relay:SILxx-1Axx-71x K1
U 1 1 607F7910
P 2350 1850
F 0 "K1" V 1783 1850 50  0000 C CNN
F 1 "SILxx-1Axx-71x" V 1874 1850 50  0000 C CNN
F 2 "Relay_THT:Relay_SPST_StandexMeder_SIL_Form1A" H 2700 1800 50  0001 L CNN
F 3 "https://standexelectronics.com/wp-content/uploads/datasheet_reed_relay_SIL.pdf" H 2350 1850 50  0001 C CNN
	1    2350 1850
	0    1    1    0   
$EndComp
Wire Wire Line
	1950 2150 1950 2050
Wire Wire Line
	1950 2050 2050 2050
$Comp
L power:GND #PWR0103
U 1 1 607F791C
P 1950 2550
F 0 "#PWR0103" H 1950 2300 50  0001 C CNN
F 1 "GND" H 1955 2377 50  0000 C CNN
F 2 "" H 1950 2550 50  0001 C CNN
F 3 "" H 1950 2550 50  0001 C CNN
	1    1950 2550
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0104
U 1 1 607F7926
P 2750 1950
F 0 "#PWR0104" H 2750 1800 50  0001 C CNN
F 1 "+5V" H 2765 2123 50  0000 C CNN
F 2 "" H 2750 1950 50  0001 C CNN
F 3 "" H 2750 1950 50  0001 C CNN
	1    2750 1950
	1    0    0    -1  
$EndComp
Wire Wire Line
	2650 2050 2750 2050
Wire Wire Line
	2750 2050 2750 1950
Text GLabel 2700 1650 2    50   UnSpc ~ 0
RSTCON_N
Text GLabel 1950 1650 0    50   UnSpc ~ 0
RSTCON_P
Text GLabel 10400 1000 0    50   UnSpc ~ 0
RSTCON_P
Text GLabel 10400 900  0    50   UnSpc ~ 0
RSTCON_N
Text GLabel 1150 2350 0    50   Input ~ 0
RSTCON_TTL
Wire Wire Line
	1950 1650 2000 1650
Wire Wire Line
	2650 1650 2700 1650
$Comp
L pspice:DIODE D1
U 1 1 607FBC75
P 2350 900
F 0 "D1" H 2350 635 50  0000 C CNN
F 1 "DIODE" H 2350 726 50  0000 C CNN
F 2 "Diode_THT:D_A-405_P7.62mm_Horizontal" H 2350 900 50  0001 C CNN
F 3 "~" H 2350 900 50  0001 C CNN
	1    2350 900 
	-1   0    0    1   
$EndComp
Wire Wire Line
	2550 900  2700 900 
Wire Wire Line
	2700 900  2700 1650
Wire Wire Line
	2150 900  2000 900 
Wire Wire Line
	2000 900  2000 1650
Connection ~ 2000 1650
Wire Wire Line
	2000 1650 2050 1650
$Comp
L pspice:DIODE D2
U 1 1 607FC61A
P 2350 3400
F 0 "D2" H 2350 3665 50  0000 C CNN
F 1 "DIODE" H 2350 3574 50  0000 C CNN
F 2 "Diode_THT:D_A-405_P7.62mm_Horizontal" H 2350 3400 50  0001 C CNN
F 3 "~" H 2350 3400 50  0001 C CNN
	1    2350 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	2650 4150 2700 4150
Wire Wire Line
	2050 4150 2000 4150
Wire Wire Line
	2000 4150 2000 3400
Wire Wire Line
	2000 3400 2150 3400
Connection ~ 2000 4150
Wire Wire Line
	2000 4150 1950 4150
Wire Wire Line
	2550 3400 2700 3400
Wire Wire Line
	2700 3400 2700 4150
Connection ~ 2700 4150
Wire Wire Line
	2700 4150 2750 4150
$Comp
L Device:R R1
U 1 1 607FE31D
P 1400 2350
F 0 "R1" V 1607 2350 50  0000 C CNN
F 1 "220" V 1516 2350 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 1330 2350 50  0001 C CNN
F 3 "~" H 1400 2350 50  0001 C CNN
	1    1400 2350
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1150 2350 1250 2350
Wire Wire Line
	1550 2350 1650 2350
$Comp
L Device:R R2
U 1 1 607FFDCB
P 1400 4850
F 0 "R2" V 1607 4850 50  0000 C CNN
F 1 "220" V 1516 4850 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 1330 4850 50  0001 C CNN
F 3 "~" H 1400 4850 50  0001 C CNN
	1    1400 4850
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1150 4850 1250 4850
Wire Wire Line
	1550 4850 1650 4850
$Comp
L esp8266:NodeMCU1.0(ESP-12E) U1
U 1 1 60812634
P 5850 2750
F 0 "U1" H 5850 3837 60  0000 C CNN
F 1 "NodeMCU1.0(ESP-12E)" H 5850 3731 60  0000 C CNN
F 2 "esp8266:NodeMCU-LoLinV3" H 5250 1900 60  0001 C CNN
F 3 "" H 5250 1900 60  0000 C CNN
	1    5850 2750
	1    0    0    -1  
$EndComp
Text GLabel 7050 2850 2    50   Output ~ 0
RSTCON_TTL
Text GLabel 7050 2750 2    50   Output ~ 0
PWRBTN_TTL
$Comp
L power:+5V #PWR0105
U 1 1 608136DB
P 4700 3300
F 0 "#PWR0105" H 4700 3150 50  0001 C CNN
F 1 "+5V" H 4715 3473 50  0000 C CNN
F 2 "" H 4700 3300 50  0001 C CNN
F 3 "" H 4700 3300 50  0001 C CNN
	1    4700 3300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0106
U 1 1 60814A75
P 4950 3050
F 0 "#PWR0106" H 4950 2800 50  0001 C CNN
F 1 "GND" H 4955 2877 50  0000 C CNN
F 2 "" H 4950 3050 50  0001 C CNN
F 3 "" H 4950 3050 50  0001 C CNN
	1    4950 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	5050 2950 4950 2950
Wire Wire Line
	4950 2950 4950 3050
$Comp
L Isolator:FODM217A U2
U 1 1 60815F8E
P 9950 3050
F 0 "U2" H 9950 3375 50  0000 C CNN
F 1 "FODM217A" H 9950 3284 50  0000 C CNN
F 2 "Package_DIP:DIP-4_W7.62mm" H 9950 2850 50  0001 C CIN
F 3 "https://www.onsemi.com/pub/Collateral/FODM214-D.PDF" H 9950 3050 50  0001 L CNN
	1    9950 3050
	-1   0    0    -1  
$EndComp
Text GLabel 10400 1300 0    50   UnSpc ~ 0
PWRLED_N
Text GLabel 10400 1400 0    50   UnSpc ~ 0
PWRLED_P
Text GLabel 10250 3150 2    50   UnSpc ~ 0
PWRLED_N
Text GLabel 10250 2950 2    50   UnSpc ~ 0
PWRLED_P
$Comp
L power:GND #PWR0107
U 1 1 6081854B
P 9250 3200
F 0 "#PWR0107" H 9250 2950 50  0001 C CNN
F 1 "GND" H 9255 3027 50  0000 C CNN
F 2 "" H 9250 3200 50  0001 C CNN
F 3 "" H 9250 3200 50  0001 C CNN
	1    9250 3200
	1    0    0    -1  
$EndComp
$Comp
L Device:R R3
U 1 1 60819301
P 9450 3150
F 0 "R3" V 9350 3150 50  0000 C CNN
F 1 "220" V 9250 3150 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 9380 3150 50  0001 C CNN
F 3 "~" H 9450 3150 50  0001 C CNN
	1    9450 3150
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9600 3150 9650 3150
Wire Wire Line
	9300 3150 9250 3150
Wire Wire Line
	9250 3150 9250 3200
$Comp
L Device:R R4
U 1 1 6081B098
P 9500 2800
F 0 "R4" H 9570 2846 50  0000 L CNN
F 1 "10k" H 9570 2755 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 9430 2800 50  0001 C CNN
F 3 "~" H 9500 2800 50  0001 C CNN
	1    9500 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	9650 2950 9500 2950
Text GLabel 7050 2150 2    50   Input ~ 0
PWRLED_TTL
Text GLabel 9250 2950 0    50   Output ~ 0
PWRLED_TTL
Wire Wire Line
	9500 2950 9250 2950
Connection ~ 9500 2950
$Comp
L power:+5V #PWR0108
U 1 1 6081D2B1
P 9500 2650
F 0 "#PWR0108" H 9500 2500 50  0001 C CNN
F 1 "+5V" H 9515 2823 50  0000 C CNN
F 2 "" H 9500 2650 50  0001 C CNN
F 3 "" H 9500 2650 50  0001 C CNN
	1    9500 2650
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D3
U 1 1 6081FCCB
P 6850 2750
F 0 "D3" H 6850 2550 50  0000 C CNN
F 1 "LED" H 6850 2650 50  0000 C CNN
F 2 "LED_THT:LED_D3.0mm" H 6850 2750 50  0001 C CNN
F 3 "~" H 6850 2750 50  0001 C CNN
	1    6850 2750
	-1   0    0    1   
$EndComp
$Comp
L Device:LED D4
U 1 1 60820B99
P 6850 2850
F 0 "D4" H 6850 3050 50  0000 C CNN
F 1 "LED" H 6850 2950 50  0000 C CNN
F 2 "LED_THT:LED_D3.0mm" H 6850 2850 50  0001 C CNN
F 3 "~" H 6850 2850 50  0001 C CNN
	1    6850 2850
	-1   0    0    1   
$EndComp
Wire Wire Line
	6650 2750 6700 2750
Wire Wire Line
	6700 2850 6650 2850
Wire Wire Line
	7000 2850 7050 2850
Wire Wire Line
	7050 2750 7000 2750
Wire Wire Line
	7050 2150 6650 2150
$Comp
L symbols:atxpanel J2
U 1 1 60826863
P 9600 1250
F 0 "J2" H 9650 1800 50  0000 R CNN
F 1 "atxpanel" H 9750 1700 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x10_P2.54mm_Horizontal" H 9600 1250 50  0001 C CNN
F 3 "" H 9600 1250 50  0001 C CNN
	1    9600 1250
	-1   0    0    1   
$EndComp
Text GLabel 9250 1200 0    50   UnSpc ~ 0
PWRBTN_P
Text GLabel 9250 1100 0    50   UnSpc ~ 0
PWRBTN_N
Text GLabel 9250 1000 0    50   UnSpc ~ 0
RSTCON_P
Text GLabel 9250 900  0    50   UnSpc ~ 0
RSTCON_N
Text GLabel 9250 1300 0    50   UnSpc ~ 0
PWRLED_N
Text GLabel 9250 1400 0    50   UnSpc ~ 0
PWRLED_P
$Comp
L Connector:Conn_01x03_Male J1
U 1 1 60828E1D
P 7100 950
F 0 "J1" H 7000 950 50  0000 C CNN
F 1 "Conn_01x03_Male" H 6700 1050 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 7100 950 50  0001 C CNN
F 3 "~" H 7100 950 50  0001 C CNN
	1    7100 950 
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0109
U 1 1 6082A6E4
P 7450 800
F 0 "#PWR0109" H 7450 650 50  0001 C CNN
F 1 "+5V" H 7465 973 50  0000 C CNN
F 2 "" H 7450 800 50  0001 C CNN
F 3 "" H 7450 800 50  0001 C CNN
	1    7450 800 
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0110
U 1 1 6082ADF4
P 7450 1100
F 0 "#PWR0110" H 7450 850 50  0001 C CNN
F 1 "GND" H 7455 927 50  0000 C CNN
F 2 "" H 7450 1100 50  0001 C CNN
F 3 "" H 7450 1100 50  0001 C CNN
	1    7450 1100
	1    0    0    -1  
$EndComp
Wire Wire Line
	7300 850  7450 850 
Wire Wire Line
	7450 850  7450 800 
Wire Wire Line
	7450 1100 7450 1050
Wire Wire Line
	7450 1050 7300 1050
Wire Wire Line
	5050 3450 4700 3450
Wire Wire Line
	4700 3300 4700 3450
$Comp
L Mechanical:MountingHole H1
U 1 1 6085F63D
P 1000 7000
F 0 "H1" H 1100 7046 50  0000 L CNN
F 1 "MountingHole" H 1100 6955 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 1000 7000 50  0001 C CNN
F 3 "~" H 1000 7000 50  0001 C CNN
	1    1000 7000
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H2
U 1 1 6085FC1D
P 1000 7200
F 0 "H2" H 1100 7246 50  0000 L CNN
F 1 "MountingHole" H 1100 7155 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 1000 7200 50  0001 C CNN
F 3 "~" H 1000 7200 50  0001 C CNN
	1    1000 7200
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H3
U 1 1 6085FD7A
P 1000 7400
F 0 "H3" H 1100 7446 50  0000 L CNN
F 1 "MountingHole" H 1100 7355 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 1000 7400 50  0001 C CNN
F 3 "~" H 1000 7400 50  0001 C CNN
	1    1000 7400
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H4
U 1 1 6085FEE1
P 1000 7600
F 0 "H4" H 1100 7646 50  0000 L CNN
F 1 "MountingHole" H 1100 7555 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 1000 7600 50  0001 C CNN
F 3 "~" H 1000 7600 50  0001 C CNN
	1    1000 7600
	1    0    0    -1  
$EndComp
$EndSCHEMATC