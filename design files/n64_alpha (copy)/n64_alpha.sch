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
L Connector:Conn_01x03_Female J1
U 1 1 5F913AC8
P 9400 2000
F 0 "J1" H 9428 2026 50  0000 L CNN
F 1 "Controller Port 1" H 9428 1935 50  0000 L CNN
F 2 "Connector_JST:JST_XH_S3B-XH-A_1x03_P2.50mm_Horizontal" H 9400 2000 50  0001 C CNN
F 3 "~" H 9400 2000 50  0001 C CNN
	1    9400 2000
	1    0    0    -1  
$EndComp
Wire Wire Line
	9200 2000 8850 2000
$Comp
L power:GND #PWR0104
U 1 1 5F921E72
P 9200 2100
F 0 "#PWR0104" H 9200 1850 50  0001 C CNN
F 1 "GND" H 9205 1927 50  0000 C CNN
F 2 "" H 9200 2100 50  0001 C CNN
F 3 "" H 9200 2100 50  0001 C CNN
	1    9200 2100
	1    0    0    -1  
$EndComp
Wire Wire Line
	9200 1700 9200 1900
$Comp
L Connector:Micro_SD_Card J12
U 1 1 5F941644
P 5400 6750
F 0 "J12" H 5350 5933 50  0000 C CNN
F 1 "Micro_SD_Card" H 5350 6024 50  0000 C CNN
F 2 "Connector_Card:microSD_HC_Hirose_DM3D-SF" H 6550 7050 50  0001 C CNN
F 3 "http://katalog.we-online.de/em/datasheet/693072010801.pdf" H 5400 6750 50  0001 C CNN
	1    5400 6750
	1    0    0    -1  
$EndComp
Text Notes 9850 1650 0    50   ~ 0
1 - 3v3 (Red)\n2 - Data (Green)\n3 - Ground (Black)
Text GLabel 7950 2000 0    50   Input ~ 0
A0
Wire Wire Line
	8650 1700 9200 1700
Wire Wire Line
	7950 2000 8350 2000
$Comp
L pspice:R R1
U 1 1 5FAE5C21
P 8100 1700
F 0 "R1" V 8305 1700 50  0000 C CNN
F 1 "5k1" V 8214 1700 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" H 8100 1700 50  0001 C CNN
F 3 "~" H 8100 1700 50  0001 C CNN
	1    8100 1700
	0    -1   -1   0   
$EndComp
Text GLabel 7850 1700 0    50   Input ~ 0
5v
Text GLabel 4500 6750 0    50   Input ~ 0
3v3
Text GLabel 4500 7050 0    50   Output ~ 0
MISO
Text GLabel 4500 6650 0    50   Input ~ 0
MOSI
Text GLabel 4500 6850 0    50   Input ~ 0
SCK
Text GLabel 4500 6550 0    50   Input ~ 0
SS
Wire Notes Line
	5650 2650 5400 2650
Wire Notes Line
	5400 2900 5650 2900
Wire Notes Line
	5850 1000 5200 1000
Wire Notes Line
	5850 2750 5850 1000
Wire Notes Line
	5200 2750 5850 2750
Wire Notes Line
	5200 1000 5200 2750
Text GLabel 5050 1200 0    50   Input ~ 0
RX
Text GLabel 5050 1100 0    50   Output ~ 0
TX
Text GLabel 5050 2300 0    50   Output ~ 0
D10
Text GLabel 5050 2400 0    50   Output ~ 0
D11
Text GLabel 5050 2500 0    50   Output ~ 0
D12
Text Notes 5500 1550 3    50   ~ 0
Arduino Nano
$Comp
L Connector:Conn_01x15_Female J6
U 1 1 5FA30365
P 5250 1800
F 0 "J6" H 5278 1780 50  0000 L CNN
F 1 "Conn_01x15_Female" H 5142 2594 50  0001 C CNN
F 2 "Connector_PinHeader_1.00mm:PinHeader_1x15_P1.00mm_Vertical" H 5250 1800 50  0001 C CNN
F 3 "~" H 5250 1800 50  0001 C CNN
	1    5250 1800
	1    0    0    1   
$EndComp
$Comp
L power:GND #PWR0107
U 1 1 5FA201FE
P 6000 1200
F 0 "#PWR0107" H 6000 950 50  0001 C CNN
F 1 "GND" V 6005 1072 50  0000 R CNN
F 2 "" H 6000 1200 50  0001 C CNN
F 3 "" H 6000 1200 50  0001 C CNN
	1    6000 1200
	0    -1   1    0   
$EndComp
Text GLabel 6000 2500 2    50   Output ~ 0
D13
Text GLabel 6000 1400 2    50   Output ~ 0
5v
Text GLabel 6000 2400 2    50   Output ~ 0
3v3
$Comp
L Connector:Conn_01x15_Female J5
U 1 1 5F9BD97B
P 5800 1800
F 0 "J5" H 5692 2593 50  0000 C CNN
F 1 "Conn_01x15_Female" H 5692 2594 50  0001 C CNN
F 2 "Connector_PinHeader_1.00mm:PinHeader_1x15_P1.00mm_Vertical" H 5800 1800 50  0001 C CNN
F 3 "~" H 5800 1800 50  0001 C CNN
	1    5800 1800
	-1   0    0    1   
$EndComp
Text GLabel 6000 2200 2    50   Output ~ 0
A0
Text GLabel 6000 2100 2    50   Output ~ 0
A1
Text GLabel 6000 2000 2    50   Output ~ 0
A2
Text GLabel 6000 1900 2    50   Output ~ 0
A3
Wire Notes Line
	5400 2650 5400 2900
Wire Notes Line
	5650 2900 5650 2650
Text Notes 8400 950  0    94   ~ 0
N64 Logic Level Shifters
Text Notes 3350 1300 2    94   ~ 0
SD Card Logic Level Shifters
$Comp
L Transistor_FET:2N7000 Q1
U 1 1 5F8E72E0
P 8650 1900
F 0 "Q1" V 8899 1900 50  0000 C CNN
F 1 "2N7000" V 8990 1900 50  0000 C CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline" H 8850 1825 50  0001 L CIN
F 3 "https://www.onsemi.com/pub/Collateral/NDS7002A-D.PDF" H 8650 1900 50  0001 L CNN
	1    8650 1900
	0    -1   1    0   
$EndComp
$Comp
L Connector:Conn_01x03_Female J2
U 1 1 600140F0
P 9400 3200
F 0 "J2" H 9428 3226 50  0000 L CNN
F 1 "Controller Port 2" H 9428 3135 50  0000 L CNN
F 2 "Connector_JST:JST_XH_S3B-XH-A_1x03_P2.50mm_Horizontal" H 9400 3200 50  0001 C CNN
F 3 "~" H 9400 3200 50  0001 C CNN
	1    9400 3200
	1    0    0    -1  
$EndComp
Wire Wire Line
	9200 3200 8850 3200
$Comp
L power:GND #PWR0101
U 1 1 600140F7
P 9200 3300
F 0 "#PWR0101" H 9200 3050 50  0001 C CNN
F 1 "GND" H 9205 3127 50  0000 C CNN
F 2 "" H 9200 3300 50  0001 C CNN
F 3 "" H 9200 3300 50  0001 C CNN
	1    9200 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	9200 2900 9200 3100
Text GLabel 7950 3200 0    50   Input ~ 0
A1
Wire Wire Line
	8650 2900 9200 2900
$Comp
L pspice:R R2
U 1 1 60014102
P 8100 2900
F 0 "R2" V 8305 2900 50  0000 C CNN
F 1 "5k1" V 8214 2900 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" H 8100 2900 50  0001 C CNN
F 3 "~" H 8100 2900 50  0001 C CNN
	1    8100 2900
	0    -1   -1   0   
$EndComp
Text GLabel 7850 2900 0    50   Input ~ 0
5v
$Comp
L Transistor_FET:2N7000 Q2
U 1 1 6001411C
P 8650 3100
F 0 "Q2" V 8899 3100 50  0000 C CNN
F 1 "2N7000" V 8990 3100 50  0000 C CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline" H 8850 3025 50  0001 L CIN
F 3 "https://www.onsemi.com/pub/Collateral/NDS7002A-D.PDF" H 8650 3100 50  0001 L CNN
	1    8650 3100
	0    -1   1    0   
$EndComp
$Comp
L Connector:Conn_01x03_Female J3
U 1 1 6005CEE7
P 9400 4400
F 0 "J3" H 9428 4426 50  0000 L CNN
F 1 "Controller Port 1" H 9428 4335 50  0000 L CNN
F 2 "Connector_JST:JST_XH_S3B-XH-A_1x03_P2.50mm_Horizontal" H 9400 4400 50  0001 C CNN
F 3 "~" H 9400 4400 50  0001 C CNN
	1    9400 4400
	1    0    0    -1  
$EndComp
Wire Wire Line
	9200 4400 8850 4400
$Comp
L power:GND #PWR0102
U 1 1 6005CEEE
P 9200 4500
F 0 "#PWR0102" H 9200 4250 50  0001 C CNN
F 1 "GND" H 9205 4327 50  0000 C CNN
F 2 "" H 9200 4500 50  0001 C CNN
F 3 "" H 9200 4500 50  0001 C CNN
	1    9200 4500
	1    0    0    -1  
$EndComp
Wire Wire Line
	9200 4100 9200 4300
Text GLabel 7950 4400 0    50   Input ~ 0
A2
Wire Wire Line
	8650 4100 9200 4100
Wire Wire Line
	7950 4400 8350 4400
$Comp
L pspice:R R3
U 1 1 6005CEF8
P 8050 4100
F 0 "R3" V 8255 4100 50  0000 C CNN
F 1 "5k1" V 8164 4100 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" H 8050 4100 50  0001 C CNN
F 3 "~" H 8050 4100 50  0001 C CNN
	1    8050 4100
	0    -1   -1   0   
$EndComp
Text GLabel 7800 4100 0    50   Input ~ 0
5v
$Comp
L Transistor_FET:2N7000 Q3
U 1 1 6005CF12
P 8650 4300
F 0 "Q3" V 8899 4300 50  0000 C CNN
F 1 "2N7000" V 8990 4300 50  0000 C CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline" H 8850 4225 50  0001 L CIN
F 3 "https://www.onsemi.com/pub/Collateral/NDS7002A-D.PDF" H 8650 4300 50  0001 L CNN
	1    8650 4300
	0    -1   1    0   
$EndComp
$Comp
L Connector:Conn_01x03_Female J4
U 1 1 60079D15
P 9400 5600
F 0 "J4" H 9428 5626 50  0000 L CNN
F 1 "4" H 9428 5535 50  0000 L CNN
F 2 "Connector_JST:JST_XH_S3B-XH-A_1x03_P2.50mm_Horizontal" H 9400 5600 50  0001 C CNN
F 3 "~" H 9400 5600 50  0001 C CNN
	1    9400 5600
	1    0    0    -1  
$EndComp
Wire Wire Line
	9200 5600 8850 5600
$Comp
L power:GND #PWR0103
U 1 1 60079D1C
P 9200 5700
F 0 "#PWR0103" H 9200 5450 50  0001 C CNN
F 1 "GND" H 9205 5527 50  0000 C CNN
F 2 "" H 9200 5700 50  0001 C CNN
F 3 "" H 9200 5700 50  0001 C CNN
	1    9200 5700
	1    0    0    -1  
$EndComp
Wire Wire Line
	9200 5300 9200 5500
Text GLabel 7950 5600 0    50   Input ~ 0
A3
Wire Wire Line
	8650 5300 9200 5300
$Comp
L Transistor_FET:2N7000 Q4
U 1 1 60079D40
P 8650 5500
F 0 "Q4" V 8899 5500 50  0000 C CNN
F 1 "2N7000" V 8990 5500 50  0000 C CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline" H 8850 5425 50  0001 L CIN
F 3 "https://www.onsemi.com/pub/Collateral/NDS7002A-D.PDF" H 8650 5500 50  0001 L CNN
	1    8650 5500
	0    -1   1    0   
$EndComp
Text GLabel 1250 2400 0    50   Input ~ 0
SS
$Comp
L pspice:R R9
U 1 1 6019B3B5
P 1650 2150
F 0 "R9" V 1855 2150 50  0000 C CNN
F 1 "5k1" V 1764 2150 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" H 1650 2150 50  0001 C CNN
F 3 "~" H 1650 2150 50  0001 C CNN
	1    1650 2150
	1    0    0    -1  
$EndComp
Text GLabel 1900 1900 1    50   Input ~ 0
3v3
Text GLabel 2850 2400 2    50   Input ~ 0
D10
Text GLabel 1250 3600 0    50   Input ~ 0
MOSI
$Comp
L pspice:R R10
U 1 1 60233D99
P 1650 3350
F 0 "R10" V 1855 3350 50  0000 C CNN
F 1 "5k1" V 1764 3350 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" H 1650 3350 50  0001 C CNN
F 3 "~" H 1650 3350 50  0001 C CNN
	1    1650 3350
	1    0    0    -1  
$EndComp
Text GLabel 1900 3100 1    50   Input ~ 0
3v3
$Comp
L Transistor_FET:2N7000 Q6
U 1 1 60233DB2
P 2150 3500
F 0 "Q6" V 2399 3500 50  0000 C CNN
F 1 "2N7000" V 2490 3500 50  0000 C CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline" H 2350 3425 50  0001 L CIN
F 3 "https://www.onsemi.com/pub/Collateral/NDS7002A-D.PDF" H 2150 3500 50  0001 L CNN
	1    2150 3500
	0    1    1    0   
$EndComp
$Comp
L pspice:R R6
U 1 1 60233DB9
P 2700 3300
F 0 "R6" V 2905 3300 50  0000 C CNN
F 1 "5k1" V 2814 3300 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" H 2700 3300 50  0001 C CNN
F 3 "~" H 2700 3300 50  0001 C CNN
	1    2700 3300
	0    1    -1   0   
$EndComp
Text GLabel 2850 3600 2    50   Input ~ 0
D11
Text GLabel 2950 3300 2    50   Input ~ 0
5v
Text GLabel 1250 4800 0    50   Input ~ 0
MISO
$Comp
L pspice:R R11
U 1 1 60239259
P 1650 4550
F 0 "R11" V 1855 4550 50  0000 C CNN
F 1 "5k1" V 1764 4550 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" H 1650 4550 50  0001 C CNN
F 3 "~" H 1650 4550 50  0001 C CNN
	1    1650 4550
	1    0    0    -1  
$EndComp
Text GLabel 1900 4300 1    50   Input ~ 0
3v3
$Comp
L pspice:R R7
U 1 1 60239279
P 2700 4500
F 0 "R7" V 2905 4500 50  0000 C CNN
F 1 "5k1" V 2814 4500 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" H 2700 4500 50  0001 C CNN
F 3 "~" H 2700 4500 50  0001 C CNN
	1    2700 4500
	0    1    -1   0   
$EndComp
Text GLabel 2850 4800 2    50   Input ~ 0
D12
Text GLabel 2950 4500 2    50   Input ~ 0
5v
Text GLabel 1250 6000 0    50   Input ~ 0
SCK
Text GLabel 1900 5500 1    50   Input ~ 0
3v3
$Comp
L Transistor_FET:2N7000 Q8
U 1 1 6023F477
P 2150 5900
F 0 "Q8" V 2399 5900 50  0000 C CNN
F 1 "2N7000" V 2490 5900 50  0000 C CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline" H 2350 5825 50  0001 L CIN
F 3 "https://www.onsemi.com/pub/Collateral/NDS7002A-D.PDF" H 2150 5900 50  0001 L CNN
	1    2150 5900
	0    1    1    0   
$EndComp
$Comp
L pspice:R R8
U 1 1 6023F47E
P 2700 5700
F 0 "R8" V 2905 5700 50  0000 C CNN
F 1 "5k1" V 2814 5700 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" H 2700 5700 50  0001 C CNN
F 3 "~" H 2700 5700 50  0001 C CNN
	1    2700 5700
	0    1    -1   0   
$EndComp
Text GLabel 2850 6000 2    50   Input ~ 0
D13
Text GLabel 2950 5700 2    50   Input ~ 0
5v
Wire Wire Line
	2350 2400 2450 2400
Wire Wire Line
	2350 3600 2450 3600
Wire Wire Line
	2350 4800 2450 4800
Wire Wire Line
	2350 6000 2450 6000
Text GLabel 7850 5300 0    50   Input ~ 0
5v
$Comp
L pspice:R R4
U 1 1 60079D26
P 8100 5300
F 0 "R4" V 8305 5300 50  0000 C CNN
F 1 "5k1" V 8214 5300 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" H 8100 5300 50  0001 C CNN
F 3 "~" H 8100 5300 50  0001 C CNN
	1    8100 5300
	0    -1   -1   0   
$EndComp
Wire Wire Line
	8350 5300 8350 5600
Wire Wire Line
	8300 4100 8350 4100
Wire Wire Line
	8350 4100 8350 4400
Connection ~ 8350 4400
Wire Wire Line
	8350 4400 8450 4400
Wire Wire Line
	8350 2900 8350 3200
Connection ~ 8350 3200
Wire Wire Line
	8350 3200 8450 3200
Wire Wire Line
	7950 3200 8350 3200
Connection ~ 8350 5600
Wire Wire Line
	8350 5600 8450 5600
Wire Wire Line
	7950 5600 8350 5600
Wire Wire Line
	8350 1700 8350 2000
Connection ~ 8350 2000
Wire Wire Line
	8350 2000 8450 2000
$Comp
L pspice:R R12
U 1 1 6023F45E
P 1650 5750
F 0 "R12" V 1855 5750 50  0000 C CNN
F 1 "5k1" V 1764 5750 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" H 1650 5750 50  0001 C CNN
F 3 "~" H 1650 5750 50  0001 C CNN
	1    1650 5750
	1    0    0    -1  
$EndComp
Wire Wire Line
	1250 6000 1650 6000
Connection ~ 1650 6000
Wire Wire Line
	1650 6000 1950 6000
Wire Wire Line
	1650 5500 2150 5500
Wire Wire Line
	2150 5500 2150 5700
Wire Wire Line
	2450 5700 2450 6000
Connection ~ 2450 6000
Wire Wire Line
	2450 6000 2850 6000
Wire Wire Line
	1650 4300 2150 4300
$Comp
L Transistor_FET:2N7000 Q7
U 1 1 60239272
P 2150 4700
F 0 "Q7" V 2399 4700 50  0000 C CNN
F 1 "2N7000" V 2490 4700 50  0000 C CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline" H 2350 4625 50  0001 L CIN
F 3 "https://www.onsemi.com/pub/Collateral/NDS7002A-D.PDF" H 2150 4700 50  0001 L CNN
	1    2150 4700
	0    1    1    0   
$EndComp
Wire Wire Line
	2450 4500 2450 4800
Connection ~ 2450 4800
Wire Wire Line
	2450 4800 2850 4800
Connection ~ 1650 4800
Wire Wire Line
	1650 4800 1950 4800
Wire Wire Line
	1250 4800 1650 4800
Wire Wire Line
	2150 4300 2150 4500
Connection ~ 1650 3600
Wire Wire Line
	1650 3600 1950 3600
Wire Wire Line
	1250 3600 1650 3600
Wire Wire Line
	1650 3100 2150 3100
Wire Wire Line
	2150 3100 2150 3300
Wire Wire Line
	2450 3300 2450 3600
Connection ~ 2450 3600
Wire Wire Line
	2450 3600 2850 3600
Text GLabel 2950 2100 2    50   Input ~ 0
5v
$Comp
L pspice:R R5
U 1 1 601BB091
P 2700 2100
F 0 "R5" V 2905 2100 50  0000 C CNN
F 1 "5k1" V 2814 2100 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" H 2700 2100 50  0001 C CNN
F 3 "~" H 2700 2100 50  0001 C CNN
	1    2700 2100
	0    1    -1   0   
$EndComp
$Comp
L Transistor_FET:2N7000 Q5
U 1 1 6019B3CF
P 2150 2300
F 0 "Q5" V 2399 2300 50  0000 C CNN
F 1 "2N7000" V 2490 2300 50  0000 C CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline" H 2350 2225 50  0001 L CIN
F 3 "https://www.onsemi.com/pub/Collateral/NDS7002A-D.PDF" H 2150 2300 50  0001 L CNN
	1    2150 2300
	0    1    1    0   
$EndComp
Wire Wire Line
	2450 2100 2450 2400
Connection ~ 2450 2400
Wire Wire Line
	2450 2400 2850 2400
Connection ~ 1650 2400
Wire Wire Line
	1650 2400 1950 2400
Wire Wire Line
	1250 2400 1650 2400
Wire Wire Line
	1650 1900 2150 1900
Wire Wire Line
	2150 1900 2150 2100
$Comp
L power:GND #PWR0105
U 1 1 60A0413B
P 5050 1400
F 0 "#PWR0105" H 5050 1150 50  0001 C CNN
F 1 "GND" V 5055 1272 50  0000 R CNN
F 2 "" H 5050 1400 50  0001 C CNN
F 3 "" H 5050 1400 50  0001 C CNN
	1    5050 1400
	0    1    -1   0   
$EndComp
$Comp
L power:GND #PWR0106
U 1 1 60A100D8
P 4500 6950
F 0 "#PWR0106" H 4500 6700 50  0001 C CNN
F 1 "GND" V 4505 6822 50  0000 R CNN
F 2 "" H 4500 6950 50  0001 C CNN
F 3 "" H 4500 6950 50  0001 C CNN
	1    4500 6950
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0108
U 1 1 5F906B3A
P 6000 1800
F 0 "#PWR0108" H 6000 1550 50  0001 C CNN
F 1 "GND" V 6005 1672 50  0000 R CNN
F 2 "" H 6000 1800 50  0001 C CNN
F 3 "" H 6000 1800 50  0001 C CNN
	1    6000 1800
	0    -1   1    0   
$EndComp
$Comp
L power:GND #PWR0109
U 1 1 5F908422
P 6000 1700
F 0 "#PWR0109" H 6000 1450 50  0001 C CNN
F 1 "GND" V 6005 1572 50  0000 R CNN
F 2 "" H 6000 1700 50  0001 C CNN
F 3 "" H 6000 1700 50  0001 C CNN
	1    6000 1700
	0    -1   1    0   
$EndComp
$Comp
L power:GND #PWR0111
U 1 1 5F9098BA
P 6000 1600
F 0 "#PWR0111" H 6000 1350 50  0001 C CNN
F 1 "GND" V 6005 1472 50  0000 R CNN
F 2 "" H 6000 1600 50  0001 C CNN
F 3 "" H 6000 1600 50  0001 C CNN
	1    6000 1600
	0    -1   1    0   
$EndComp
$Comp
L power:GND #PWR0112
U 1 1 5F90ADED
P 6000 1500
F 0 "#PWR0112" H 6000 1250 50  0001 C CNN
F 1 "GND" V 6005 1372 50  0000 R CNN
F 2 "" H 6000 1500 50  0001 C CNN
F 3 "" H 6000 1500 50  0001 C CNN
	1    6000 1500
	0    -1   1    0   
$EndComp
Text GLabel 5050 1500 0    50   Input ~ 0
INT1
$Comp
L pspice:DIODE D1
U 1 1 5F92656C
P 4850 3900
F 0 "D1" H 4850 4165 50  0000 C CNN
F 1 "DIODE" H 4850 4074 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" H 4850 3900 50  0001 C CNN
F 3 "~" H 4850 3900 50  0001 C CNN
	1    4850 3900
	0    -1   -1   0   
$EndComp
$Comp
L pspice:DIODE D2
U 1 1 5F928C0B
P 5250 3900
F 0 "D2" H 5250 4165 50  0000 C CNN
F 1 "DIODE" H 5250 4074 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" H 5250 3900 50  0001 C CNN
F 3 "~" H 5250 3900 50  0001 C CNN
	1    5250 3900
	0    -1   -1   0   
$EndComp
$Comp
L pspice:DIODE D3
U 1 1 5F92A11E
P 5650 3900
F 0 "D3" H 5650 4165 50  0000 C CNN
F 1 "DIODE" H 5650 4074 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" H 5650 3900 50  0001 C CNN
F 3 "~" H 5650 3900 50  0001 C CNN
	1    5650 3900
	0    -1   -1   0   
$EndComp
$Comp
L pspice:DIODE D4
U 1 1 5F92BA5E
P 6050 3900
F 0 "D4" H 6050 4165 50  0000 C CNN
F 1 "DIODE" H 6050 4074 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" H 6050 3900 50  0001 C CNN
F 3 "~" H 6050 3900 50  0001 C CNN
	1    6050 3900
	0    -1   -1   0   
$EndComp
Text GLabel 4850 3700 1    50   Output ~ 0
A0
Text GLabel 5250 3700 1    50   Output ~ 0
A1
Text GLabel 5650 3700 1    50   Output ~ 0
A2
Text GLabel 6050 3700 1    50   Output ~ 0
A3
Wire Wire Line
	4850 4100 4850 4150
Wire Wire Line
	4850 4150 5250 4150
Wire Wire Line
	6050 4150 6050 4100
Wire Wire Line
	5650 4100 5650 4150
Connection ~ 5650 4150
Wire Wire Line
	5650 4150 6050 4150
Wire Wire Line
	5250 4100 5250 4150
Connection ~ 5250 4150
Wire Wire Line
	5250 4150 5450 4150
Wire Wire Line
	5450 4150 5450 4300
Connection ~ 5450 4150
Wire Wire Line
	5450 4150 5650 4150
Text GLabel 5450 4300 3    50   Input ~ 0
INT1
Text Notes 5750 3450 2    50   ~ 0
Interrup Circuitry
$EndSCHEMATC
