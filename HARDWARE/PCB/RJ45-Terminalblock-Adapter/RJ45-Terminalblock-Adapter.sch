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
L Connector:RJ45 J1
U 1 1 60C8651F
P 3700 3550
F 0 "J1" H 3757 4217 50  0000 C CNN
F 1 "RJ45" H 3757 4126 50  0000 C CNN
F 2 "Clockdiv-KiCad:RJ45_Conrad_1586526" V 3700 3575 50  0001 C CNN
F 3 "~" V 3700 3575 50  0001 C CNN
	1    3700 3550
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x04 J3
U 1 1 60C884EF
P 5100 3650
F 0 "J3" H 5180 3642 50  0000 L CNN
F 1 "Conn_01x04 5.08" H 5180 3551 50  0000 L CNN
F 2 "Clockdiv-KiCad:Terminalblock_1x4_5.08mm" H 5100 3650 50  0001 C CNN
F 3 "~" H 5100 3650 50  0001 C CNN
	1    5100 3650
	1    0    0    -1  
$EndComp
$Comp
L Connector:Screw_Terminal_01x03 J2
U 1 1 60C89BE5
P 5100 3250
F 0 "J2" H 5180 3292 50  0000 L CNN
F 1 "Screw_Terminal_01x03" H 5180 3201 50  0000 L CNN
F 2 "TerminalBlock_MetzConnect:TerminalBlock_MetzConnect_Type011_RT05503HBWC_1x03_P5.00mm_Horizontal" H 5100 3250 50  0001 C CNN
F 3 "~" H 5100 3250 50  0001 C CNN
	1    5100 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	4900 3250 4100 3250
Text Label 4400 3250 0    50   ~ 0
GND
Wire Wire Line
	4100 3150 4900 3150
Text Label 4300 3150 0    50   ~ 0
END_SW_1
Wire Wire Line
	4100 3350 4900 3350
Text Label 4300 3350 0    50   ~ 0
END_SW_2
Text Label 4100 3850 0    50   ~ 0
DIR
Text Label 4300 3750 2    50   ~ 0
5V
Text Label 4100 3650 0    50   ~ 0
STEP
$Comp
L Connector_Generic:Conn_01x04 J4
U 1 1 60C8D00E
P 5100 4150
F 0 "J4" H 5180 4142 50  0000 L CNN
F 1 "Conn_01x04 3.81" H 5180 4051 50  0000 L CNN
F 2 "Clockdiv-KiCad:Terminalblock_1x4_3.81mm" H 5100 4150 50  0001 C CNN
F 3 "~" H 5100 4150 50  0001 C CNN
	1    5100 4150
	1    0    0    -1  
$EndComp
Wire Wire Line
	4600 4250 4900 4250
Wire Wire Line
	4500 4150 4900 4150
Wire Wire Line
	4600 3550 4900 3550
Wire Wire Line
	4100 3750 4300 3750
Text Label 4600 3550 0    50   ~ 0
5V
Wire Wire Line
	4900 3750 4600 3750
Text Label 4600 3750 0    50   ~ 0
5V
Wire Wire Line
	4100 3650 4900 3650
Wire Wire Line
	4100 3850 4900 3850
Text Label 4600 4050 0    50   ~ 0
STEP
Text Label 4500 4150 0    50   ~ 0
DIR
Text Label 4600 4250 0    50   ~ 0
5V
Wire Wire Line
	4900 4050 4600 4050
NoConn ~ 4900 4350
$Comp
L Connector:Conn_01x02_Male J5
U 1 1 60C900D8
P 4300 3550
F 0 "J5" H 4272 3432 50  0000 R CNN
F 1 "Conn_01x02_Male" H 4272 3523 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 4300 3550 50  0001 C CNN
F 3 "~" H 4300 3550 50  0001 C CNN
	1    4300 3550
	-1   0    0    1   
$EndComp
$EndSCHEMATC
