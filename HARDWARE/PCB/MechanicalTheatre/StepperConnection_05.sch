EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 6 15
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
L Clockdiv-KiCad-library:RJ45x8 J?
U 5 1 60D39B1D
P 7500 4000
AR Path="/6111FD42/60D39B1D" Ref="J?"  Part="1" 
AR Path="/611E4BD8/60D39B1D" Ref="J11"  Part="5" 
AR Path="/60D39B1D" Ref="J11"  Part="5" 
F 0 "J11" H 7557 4667 50  0000 C CNN
F 1 "RJ45 8x Socket" H 7557 4576 50  0000 C CNN
F 2 "Clockdiv-KiCad:RJ45_Conrad_8x" V 7500 4025 50  0001 C CNN
F 3 "~" V 7500 4025 50  0001 C CNN
	5    7500 4000
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60D39B23
P 7100 4300
AR Path="/6111FD42/60D39B23" Ref="#PWR?"  Part="1" 
AR Path="/611E4BD8/60D39B23" Ref="#PWR095"  Part="1" 
F 0 "#PWR095" H 7100 4050 50  0001 C CNN
F 1 "GND" V 7100 4200 50  0000 R CNN
F 2 "" H 7100 4300 50  0001 C CNN
F 3 "" H 7100 4300 50  0001 C CNN
	1    7100 4300
	0    1    1    0   
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 60D39B29
P 7100 3800
AR Path="/6111FD42/60D39B29" Ref="#PWR?"  Part="1" 
AR Path="/611E4BD8/60D39B29" Ref="#PWR094"  Part="1" 
F 0 "#PWR094" H 7100 3650 50  0001 C CNN
F 1 "+5V" V 7115 3928 50  0000 L CNN
F 2 "" H 7100 3800 50  0001 C CNN
F 3 "" H 7100 3800 50  0001 C CNN
	1    7100 3800
	0    -1   -1   0   
$EndComp
$Comp
L Clockdiv-KiCad-library:SN74AHCT125N U?
U 2 1 60D39B2F
P 5350 3650
AR Path="/6111FD42/60D39B2F" Ref="U?"  Part="2" 
AR Path="/611E4BD8/60D39B2F" Ref="U8"  Part="2" 
F 0 "U8" H 5550 3550 50  0000 C CNN
F 1 "SN74AHCT125N" H 5700 3800 50  0000 C CNN
F 2 "Package_SO:SO-14_5.3x10.2mm_P1.27mm" H 5350 3650 50  0001 C CNN
F 3 "https://www.ti.com/general/docs/suppproductinfo.tsp?distId=10&gotoUrl=https%3A%2F%2Fwww.ti.com%2Flit%2Fgpn%2Fsn74ahct125" H 5350 3650 50  0001 C CNN
	2    5350 3650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60D39B35
P 5050 3600
AR Path="/6111FD42/60D39B35" Ref="#PWR?"  Part="1" 
AR Path="/611E4BD8/60D39B35" Ref="#PWR087"  Part="1" 
F 0 "#PWR087" H 5050 3350 50  0001 C CNN
F 1 "GND" V 5055 3472 50  0000 R CNN
F 2 "" H 5050 3600 50  0001 C CNN
F 3 "" H 5050 3600 50  0001 C CNN
	1    5050 3600
	0    1    1    0   
$EndComp
Wire Wire Line
	5050 3700 4700 3700
$Comp
L Clockdiv-KiCad-library:SN74HC14S U?
U 5 1 60D39B3C
P 5650 5050
AR Path="/6111FD42/60D39B3C" Ref="U?"  Part="1" 
AR Path="/611E4BD8/60D39B3C" Ref="U6"  Part="5" 
F 0 "U6" H 5900 5150 50  0000 R CNN
F 1 "SN74HC14S" H 6150 4950 50  0000 R CNN
F 2 "Package_SO:SO-14_5.3x10.2mm_P1.27mm" H 5650 5050 50  0001 C CNN
F 3 "https://www.ti.com/lit/gpn/sn74hc14" H 5650 5050 50  0001 C CNN
	5    5650 5050
	-1   0    0    -1  
$EndComp
Wire Wire Line
	5350 5050 4700 5050
$Comp
L power:+3.3V #PWR?
U 1 1 60D39B49
P 5800 4650
AR Path="/6111FD42/60D39B49" Ref="#PWR?"  Part="1" 
AR Path="/611E4BD8/60D39B49" Ref="#PWR091"  Part="1" 
F 0 "#PWR091" H 5800 4500 50  0001 C CNN
F 1 "+3.3V" V 5800 4750 50  0000 L CNN
F 2 "" H 5800 4650 50  0001 C CNN
F 3 "" H 5800 4650 50  0001 C CNN
	1    5800 4650
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 60D39B4F
P 6650 4900
AR Path="/6111FD42/60D39B4F" Ref="R?"  Part="1" 
AR Path="/611E4BD8/60D39B4F" Ref="R31"  Part="1" 
F 0 "R31" H 6720 4946 50  0000 L CNN
F 1 "1k" H 6720 4855 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 6580 4900 50  0001 C CNN
F 3 "~" H 6650 4900 50  0001 C CNN
	1    6650 4900
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 60D39B55
P 6250 4900
AR Path="/6111FD42/60D39B55" Ref="R?"  Part="1" 
AR Path="/611E4BD8/60D39B55" Ref="R30"  Part="1" 
F 0 "R30" H 6180 4854 50  0000 R CNN
F 1 "10k" H 6180 4945 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 6180 4900 50  0001 C CNN
F 3 "~" H 6250 4900 50  0001 C CNN
	1    6250 4900
	-1   0    0    1   
$EndComp
Wire Wire Line
	5950 5050 6250 5050
Connection ~ 6250 5050
$Comp
L Device:C C?
U 1 1 60D39B5E
P 6250 5200
AR Path="/6111FD42/60D39B5E" Ref="C?"  Part="1" 
AR Path="/611E4BD8/60D39B5E" Ref="C8"  Part="1" 
F 0 "C8" H 6365 5246 50  0000 L CNN
F 1 "0.1uF 16V" H 6365 5155 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 6288 5050 50  0001 C CNN
F 3 "~" H 6250 5200 50  0001 C CNN
	1    6250 5200
	1    0    0    -1  
$EndComp
Wire Wire Line
	5700 5350 6250 5350
Wire Wire Line
	6250 4750 5700 4750
Wire Wire Line
	6250 5050 6650 5050
Wire Wire Line
	5700 4750 5700 4650
Wire Wire Line
	5700 4650 5800 4650
$Comp
L Clockdiv-KiCad-library:SN74AHCT125N U?
U 1 1 60D39B7B
P 5350 3100
AR Path="/6111FD42/60D39B7B" Ref="U?"  Part="1" 
AR Path="/611E4BD8/60D39B7B" Ref="U8"  Part="1" 
F 0 "U8" H 5450 3000 50  0000 L CNN
F 1 "SN74AHCT125N" H 5400 3250 50  0000 L CNN
F 2 "Package_SO:SO-14_5.3x10.2mm_P1.27mm" H 5350 3100 50  0001 C CNN
F 3 "https://www.ti.com/general/docs/suppproductinfo.tsp?distId=10&gotoUrl=https%3A%2F%2Fwww.ti.com%2Flit%2Fgpn%2Fsn74ahct125" H 5350 3100 50  0001 C CNN
	1    5350 3100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60D39B81
P 5300 3300
AR Path="/6111FD42/60D39B81" Ref="#PWR?"  Part="1" 
AR Path="/611E4BD8/60D39B81" Ref="#PWR089"  Part="1" 
F 0 "#PWR089" H 5300 3050 50  0001 C CNN
F 1 "GND" H 5250 3250 50  0000 R CNN
F 2 "" H 5300 3300 50  0001 C CNN
F 3 "" H 5300 3300 50  0001 C CNN
	1    5300 3300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60D39B87
P 5050 3050
AR Path="/6111FD42/60D39B87" Ref="#PWR?"  Part="1" 
AR Path="/611E4BD8/60D39B87" Ref="#PWR086"  Part="1" 
F 0 "#PWR086" H 5050 2800 50  0001 C CNN
F 1 "GND" V 5055 2922 50  0000 R CNN
F 2 "" H 5050 3050 50  0001 C CNN
F 3 "" H 5050 3050 50  0001 C CNN
	1    5050 3050
	0    1    1    0   
$EndComp
Text Label 3850 2150 0    200  ~ 0
STEPPER_MOTOR_CONNECTION_5
Text Notes 7050 3450 2    50   ~ 0
DIR
Text Notes 6700 3600 2    50   ~ 0
STEP
Text Notes 7050 4200 2    50   ~ 0
END 2
Text Notes 7050 4400 2    50   ~ 0
END 1
Wire Wire Line
	6900 3100 6900 3700
Wire Wire Line
	6900 3700 7100 3700
Wire Wire Line
	6650 4400 7100 4400
$Comp
L Connector:Conn_01x02_Male J?
U 1 1 60D39B9B
P 5650 4000
AR Path="/6111FD42/60D39B9B" Ref="J?"  Part="1" 
AR Path="/611E4BD8/60D39B9B" Ref="J13"  Part="1" 
F 0 "J13" H 5700 4050 25  0000 C CNN
F 1 "Conn_01x02_General Purpose 05" H 5250 4050 25  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 5650 4000 50  0001 C CNN
F 3 "~" H 5650 4000 50  0001 C CNN
	1    5650 4000
	1    0    0    -1  
$EndComp
Wire Wire Line
	5650 3100 6900 3100
Wire Wire Line
	5650 3650 6750 3650
Wire Wire Line
	6750 3650 6750 3900
Wire Wire Line
	6750 3900 7100 3900
Wire Wire Line
	6650 4400 6650 4750
$Comp
L power:GND #PWR?
U 1 1 60D39BA6
P 6150 3900
AR Path="/6111FD42/60D39BA6" Ref="#PWR?"  Part="1" 
AR Path="/611E4BD8/60D39BA6" Ref="#PWR092"  Part="1" 
F 0 "#PWR092" H 6150 3650 50  0001 C CNN
F 1 "GND" V 6150 3750 50  0000 R CNN
F 2 "" H 6150 3900 50  0001 C CNN
F 3 "" H 6150 3900 50  0001 C CNN
	1    6150 3900
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R?
U 1 1 60D39BAC
P 6000 4200
AR Path="/6111FD42/60D39BAC" Ref="R?"  Part="1" 
AR Path="/611E4BD8/60D39BAC" Ref="R29"  Part="1" 
F 0 "R29" V 6000 4250 50  0000 R CNN
F 1 "10k" V 5930 4245 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 5930 4200 50  0001 C CNN
F 3 "~" H 6000 4200 50  0001 C CNN
	1    6000 4200
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R?
U 1 1 60D39BB2
P 6000 3900
AR Path="/6111FD42/60D39BB2" Ref="R?"  Part="1" 
AR Path="/611E4BD8/60D39BB2" Ref="R28"  Part="1" 
F 0 "R28" V 6000 3950 50  0000 R CNN
F 1 "10k" V 6100 3950 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 5930 3900 50  0001 C CNN
F 3 "~" H 6000 3900 50  0001 C CNN
	1    6000 3900
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60D39BB8
P 6150 4200
AR Path="/6111FD42/60D39BB8" Ref="#PWR?"  Part="1" 
AR Path="/611E4BD8/60D39BB8" Ref="#PWR093"  Part="1" 
F 0 "#PWR093" H 6150 3950 50  0001 C CNN
F 1 "GND" V 6150 4050 50  0000 R CNN
F 2 "" H 6150 4200 50  0001 C CNN
F 3 "" H 6150 4200 50  0001 C CNN
	1    6150 4200
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5850 3900 5850 4000
Wire Wire Line
	5850 4100 5850 4200
Wire Wire Line
	5850 4000 7100 4000
Connection ~ 5850 4000
Wire Wire Line
	5850 4100 7100 4100
Connection ~ 5850 4100
Wire Wire Line
	7100 4200 6550 4200
Wire Wire Line
	6550 4200 6550 4400
Text Notes 4850 4150 0    25   ~ 0
simply two unused lines from cat cable. \npulled to gnd if unused, otherwise for\nprototyping / testing..
Text HLabel 4700 3150 0    50   Input ~ 0
Stepper_DIR
Wire Wire Line
	4700 3150 5050 3150
Text HLabel 4700 3700 0    50   Input ~ 0
Stepper_STEP
Text HLabel 4700 5050 0    50   Output ~ 0
Stepper_END
Text HLabel 4700 4400 0    50   Output ~ 0
END_ALL
Wire Wire Line
	4700 4400 6550 4400
$Comp
L power:GND #PWR?
U 1 1 60D39B43
P 5700 5350
AR Path="/6111FD42/60D39B43" Ref="#PWR?"  Part="1" 
AR Path="/611E4BD8/60D39B43" Ref="#PWR090"  Part="1" 
F 0 "#PWR090" H 5700 5100 50  0001 C CNN
F 1 "GND" H 5650 5300 50  0000 R CNN
F 2 "" H 5700 5350 50  0001 C CNN
F 3 "" H 5700 5350 50  0001 C CNN
	1    5700 5350
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 6256C5F4
P 5300 2500
AR Path="/6111FD42/6256C5F4" Ref="#PWR?"  Part="1" 
AR Path="/611E3121/6256C5F4" Ref="#PWR?"  Part="1" 
AR Path="/611E4BD8/6256C5F4" Ref="#PWR0107"  Part="1" 
F 0 "#PWR0107" H 5300 2350 50  0001 C CNN
F 1 "+5V" H 5100 2550 50  0000 L CNN
F 2 "" H 5300 2500 50  0001 C CNN
F 3 "" H 5300 2500 50  0001 C CNN
	1    5300 2500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 6256C5FA
P 4800 2750
AR Path="/6111FD42/6256C5FA" Ref="#PWR?"  Part="1" 
AR Path="/611E4BD8/6256C5FA" Ref="#PWR088"  Part="1" 
F 0 "#PWR088" H 4800 2500 50  0001 C CNN
F 1 "GND" V 4800 2650 50  0000 R CNN
F 2 "" H 4800 2750 50  0001 C CNN
F 3 "" H 4800 2750 50  0001 C CNN
	1    4800 2750
	0    1    1    0   
$EndComp
Wire Wire Line
	4800 2750 5000 2750
$Comp
L Device:C C?
U 1 1 6256C602
P 5150 2750
AR Path="/6111FD42/6256C602" Ref="C?"  Part="1" 
AR Path="/611E3121/6256C602" Ref="C?"  Part="1" 
AR Path="/611E4BD8/6256C602" Ref="C27"  Part="1" 
F 0 "C27" V 5100 2800 50  0000 L CNN
F 1 "0.1uF 16V " V 5250 2550 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 5188 2600 50  0001 C CNN
F 3 "~" H 5150 2750 50  0001 C CNN
F 4 "place near SN74AHCT125N" V 5250 2050 50  0000 C CNN "Comment"
	1    5150 2750
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5300 2500 5300 2750
Wire Wire Line
	5300 2750 5300 2900
Connection ~ 5300 2750
$EndSCHEMATC
