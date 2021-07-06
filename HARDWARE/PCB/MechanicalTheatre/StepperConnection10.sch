EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 9 15
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
U 2 1 60D978AB
P 7300 4100
AR Path="/6111FD42/60D978AB" Ref="J?"  Part="1" 
AR Path="/60D6F6F4/60D978AB" Ref="J12"  Part="2" 
F 0 "J12" H 7357 4767 50  0000 C CNN
F 1 "RJ45 8x Socket" H 7357 4676 50  0000 C CNN
F 2 "Clockdiv-KiCad:RJ45_Conrad_8x" V 7300 4125 50  0001 C CNN
F 3 "~" V 7300 4125 50  0001 C CNN
	2    7300 4100
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60D978B1
P 6900 4400
AR Path="/6111FD42/60D978B1" Ref="#PWR?"  Part="1" 
AR Path="/60D6F6F4/60D978B1" Ref="#PWR0122"  Part="1" 
F 0 "#PWR0122" H 6900 4150 50  0001 C CNN
F 1 "GND" V 6900 4300 50  0000 R CNN
F 2 "" H 6900 4400 50  0001 C CNN
F 3 "" H 6900 4400 50  0001 C CNN
	1    6900 4400
	0    1    1    0   
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 60D978B7
P 6900 3900
AR Path="/6111FD42/60D978B7" Ref="#PWR?"  Part="1" 
AR Path="/60D6F6F4/60D978B7" Ref="#PWR0121"  Part="1" 
F 0 "#PWR0121" H 6900 3750 50  0001 C CNN
F 1 "+5V" V 6915 4028 50  0000 L CNN
F 2 "" H 6900 3900 50  0001 C CNN
F 3 "" H 6900 3900 50  0001 C CNN
	1    6900 3900
	0    -1   -1   0   
$EndComp
$Comp
L Clockdiv-KiCad-library:SN74AHCT125N U?
U 4 1 60D978BD
P 5150 3750
AR Path="/6111FD42/60D978BD" Ref="U?"  Part="2" 
AR Path="/60D6F6F4/60D978BD" Ref="U11"  Part="4" 
F 0 "U11" H 5350 3650 50  0000 C CNN
F 1 "SN74AHCT125N" H 5500 3900 50  0000 C CNN
F 2 "Package_SO:SO-14_5.3x10.2mm_P1.27mm" H 5150 3750 50  0001 C CNN
F 3 "https://www.ti.com/general/docs/suppproductinfo.tsp?distId=10&gotoUrl=https%3A%2F%2Fwww.ti.com%2Flit%2Fgpn%2Fsn74ahct125" H 5150 3750 50  0001 C CNN
	4    5150 3750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60D978C3
P 4850 3700
AR Path="/6111FD42/60D978C3" Ref="#PWR?"  Part="1" 
AR Path="/60D6F6F4/60D978C3" Ref="#PWR0116"  Part="1" 
F 0 "#PWR0116" H 4850 3450 50  0001 C CNN
F 1 "GND" V 4855 3572 50  0000 R CNN
F 2 "" H 4850 3700 50  0001 C CNN
F 3 "" H 4850 3700 50  0001 C CNN
	1    4850 3700
	0    1    1    0   
$EndComp
Wire Wire Line
	4850 3800 4500 3800
$Comp
L Clockdiv-KiCad-library:SN74HC14S U?
U 4 1 60D978CA
P 5450 5150
AR Path="/6111FD42/60D978CA" Ref="U?"  Part="1" 
AR Path="/60D6F6F4/60D978CA" Ref="U10"  Part="4" 
F 0 "U10" H 5700 5250 50  0000 R CNN
F 1 "SN74HC14S" H 5950 5050 50  0000 R CNN
F 2 "Package_SO:SO-14_5.3x10.2mm_P1.27mm" H 5450 5150 50  0001 C CNN
F 3 "https://www.ti.com/lit/gpn/sn74hc14" H 5450 5150 50  0001 C CNN
	4    5450 5150
	-1   0    0    -1  
$EndComp
Wire Wire Line
	5150 5150 4500 5150
$Comp
L power:GND #PWR?
U 1 1 60D978D1
P 5500 5450
AR Path="/6111FD42/60D978D1" Ref="#PWR?"  Part="1" 
AR Path="/60D6F6F4/60D978D1" Ref="#PWR0117"  Part="1" 
F 0 "#PWR0117" H 5500 5200 50  0001 C CNN
F 1 "GND" H 5450 5400 50  0000 R CNN
F 2 "" H 5500 5450 50  0001 C CNN
F 3 "" H 5500 5450 50  0001 C CNN
	1    5500 5450
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 60D978D7
P 5600 4750
AR Path="/6111FD42/60D978D7" Ref="#PWR?"  Part="1" 
AR Path="/60D6F6F4/60D978D7" Ref="#PWR0118"  Part="1" 
F 0 "#PWR0118" H 5600 4600 50  0001 C CNN
F 1 "+3.3V" V 5600 4850 50  0000 L CNN
F 2 "" H 5600 4750 50  0001 C CNN
F 3 "" H 5600 4750 50  0001 C CNN
	1    5600 4750
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 60D978DD
P 6450 5000
AR Path="/6111FD42/60D978DD" Ref="R?"  Part="1" 
AR Path="/60D6F6F4/60D978DD" Ref="R43"  Part="1" 
F 0 "R43" H 6520 5046 50  0000 L CNN
F 1 "1k" H 6520 4955 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 6380 5000 50  0001 C CNN
F 3 "~" H 6450 5000 50  0001 C CNN
	1    6450 5000
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 60D978E3
P 6050 5000
AR Path="/6111FD42/60D978E3" Ref="R?"  Part="1" 
AR Path="/60D6F6F4/60D978E3" Ref="R42"  Part="1" 
F 0 "R42" H 5980 4954 50  0000 R CNN
F 1 "10k" H 5980 5045 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 5980 5000 50  0001 C CNN
F 3 "~" H 6050 5000 50  0001 C CNN
	1    6050 5000
	-1   0    0    1   
$EndComp
Wire Wire Line
	5750 5150 6050 5150
Connection ~ 6050 5150
$Comp
L Device:C C?
U 1 1 60D978EC
P 6050 5300
AR Path="/6111FD42/60D978EC" Ref="C?"  Part="1" 
AR Path="/60D6F6F4/60D978EC" Ref="C12"  Part="1" 
F 0 "C12" H 6165 5346 50  0000 L CNN
F 1 "0.1uF 16V" H 6165 5255 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 6088 5150 50  0001 C CNN
F 3 "~" H 6050 5300 50  0001 C CNN
	1    6050 5300
	1    0    0    -1  
$EndComp
Wire Wire Line
	5500 5450 6050 5450
Wire Wire Line
	6050 4850 5500 4850
Wire Wire Line
	6050 5150 6450 5150
Wire Wire Line
	5500 4850 5500 4750
Wire Wire Line
	5500 4750 5600 4750
$Comp
L Clockdiv-KiCad-library:SN74AHCT125N U?
U 3 1 60D97909
P 5150 3200
AR Path="/6111FD42/60D97909" Ref="U?"  Part="1" 
AR Path="/60D6F6F4/60D97909" Ref="U11"  Part="3" 
F 0 "U11" H 5250 3100 50  0000 L CNN
F 1 "SN74AHCT125N" H 5200 3350 50  0000 L CNN
F 2 "Package_SO:SO-14_5.3x10.2mm_P1.27mm" H 5150 3200 50  0001 C CNN
F 3 "https://www.ti.com/general/docs/suppproductinfo.tsp?distId=10&gotoUrl=https%3A%2F%2Fwww.ti.com%2Flit%2Fgpn%2Fsn74ahct125" H 5150 3200 50  0001 C CNN
	3    5150 3200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60D97915
P 4850 3150
AR Path="/6111FD42/60D97915" Ref="#PWR?"  Part="1" 
AR Path="/60D6F6F4/60D97915" Ref="#PWR0115"  Part="1" 
F 0 "#PWR0115" H 4850 2900 50  0001 C CNN
F 1 "GND" V 4855 3022 50  0000 R CNN
F 2 "" H 4850 3150 50  0001 C CNN
F 3 "" H 4850 3150 50  0001 C CNN
	1    4850 3150
	0    1    1    0   
$EndComp
Text Label 3650 2750 0    200  ~ 0
STEPPER_MOTOR_CONNECTION_10
Text Notes 6850 3550 2    50   ~ 0
DIR
Text Notes 6500 3700 2    50   ~ 0
STEP
Text Notes 6850 4300 2    50   ~ 0
END 2
Text Notes 6850 4500 2    50   ~ 0
END 1
Wire Wire Line
	6700 3200 6700 3800
Wire Wire Line
	6700 3800 6900 3800
Wire Wire Line
	6450 4500 6900 4500
$Comp
L Connector:Conn_01x02_Male J?
U 1 1 60D97929
P 5450 4100
AR Path="/6111FD42/60D97929" Ref="J?"  Part="1" 
AR Path="/60D6F6F4/60D97929" Ref="J16"  Part="1" 
F 0 "J16" H 5500 4150 25  0000 C CNN
F 1 "Conn_01x02_General Purpose 10" H 5050 4150 25  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 5450 4100 50  0001 C CNN
F 3 "~" H 5450 4100 50  0001 C CNN
	1    5450 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	5450 3200 6700 3200
Wire Wire Line
	5450 3750 6550 3750
Wire Wire Line
	6550 3750 6550 4000
Wire Wire Line
	6550 4000 6900 4000
Wire Wire Line
	6450 4500 6450 4850
$Comp
L power:GND #PWR?
U 1 1 60D97934
P 5950 4000
AR Path="/6111FD42/60D97934" Ref="#PWR?"  Part="1" 
AR Path="/60D6F6F4/60D97934" Ref="#PWR0119"  Part="1" 
F 0 "#PWR0119" H 5950 3750 50  0001 C CNN
F 1 "GND" V 5950 3850 50  0000 R CNN
F 2 "" H 5950 4000 50  0001 C CNN
F 3 "" H 5950 4000 50  0001 C CNN
	1    5950 4000
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R?
U 1 1 60D9793A
P 5800 4300
AR Path="/6111FD42/60D9793A" Ref="R?"  Part="1" 
AR Path="/60D6F6F4/60D9793A" Ref="R41"  Part="1" 
F 0 "R41" V 5800 4350 50  0000 R CNN
F 1 "10k" V 5730 4345 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 5730 4300 50  0001 C CNN
F 3 "~" H 5800 4300 50  0001 C CNN
	1    5800 4300
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R?
U 1 1 60D97940
P 5800 4000
AR Path="/6111FD42/60D97940" Ref="R?"  Part="1" 
AR Path="/60D6F6F4/60D97940" Ref="R40"  Part="1" 
F 0 "R40" V 5800 4050 50  0000 R CNN
F 1 "10k" V 5900 4050 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 5730 4000 50  0001 C CNN
F 3 "~" H 5800 4000 50  0001 C CNN
	1    5800 4000
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60D97946
P 5950 4300
AR Path="/6111FD42/60D97946" Ref="#PWR?"  Part="1" 
AR Path="/60D6F6F4/60D97946" Ref="#PWR0120"  Part="1" 
F 0 "#PWR0120" H 5950 4050 50  0001 C CNN
F 1 "GND" V 5950 4150 50  0000 R CNN
F 2 "" H 5950 4300 50  0001 C CNN
F 3 "" H 5950 4300 50  0001 C CNN
	1    5950 4300
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5650 4000 5650 4100
Wire Wire Line
	5650 4200 5650 4300
Wire Wire Line
	5650 4100 6900 4100
Connection ~ 5650 4100
Wire Wire Line
	5650 4200 6900 4200
Connection ~ 5650 4200
Wire Wire Line
	6900 4300 6350 4300
Wire Wire Line
	6350 4300 6350 4500
Text Notes 4650 4250 0    25   ~ 0
simply two unused lines from cat cable. \npulled to gnd if unused, otherwise for\nprototyping / testing..
Text HLabel 4500 3250 0    50   Input ~ 0
Stepper_DIR
Wire Wire Line
	4500 3250 4850 3250
Text HLabel 4500 3800 0    50   Input ~ 0
Stepper_STEP
Text HLabel 4500 5150 0    50   Output ~ 0
Stepper_END
Text HLabel 4500 4500 0    50   Output ~ 0
END_ALL
Wire Wire Line
	4500 4500 6350 4500
$EndSCHEMATC
