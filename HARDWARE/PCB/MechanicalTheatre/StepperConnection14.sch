EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 15 15
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
L MechanicalTheatre-rescue:RJ45x8-Clockdiv-KiCad-library J?
U 6 1 60F28967
P 7300 4200
AR Path="/6111FD42/60F28967" Ref="J?"  Part="1" 
AR Path="/60F0CD1D/60F28967" Ref="J12"  Part="6" 
AR Path="/60F28967" Ref="J12"  Part="6" 
F 0 "J12" H 7357 4867 50  0000 C CNN
F 1 "RJ45 8x Socket" H 7357 4776 50  0000 C CNN
F 2 "Clockdiv-KiCad:RJ45_Conrad_8x" V 7300 4225 50  0001 C CNN
F 3 "~" V 7300 4225 50  0001 C CNN
	6    7300 4200
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60F2896D
P 6900 4500
AR Path="/6111FD42/60F2896D" Ref="#PWR?"  Part="1" 
AR Path="/60F0CD1D/60F2896D" Ref="#PWR0180"  Part="1" 
F 0 "#PWR0180" H 6900 4250 50  0001 C CNN
F 1 "GND" V 6900 4400 50  0000 R CNN
F 2 "" H 6900 4500 50  0001 C CNN
F 3 "" H 6900 4500 50  0001 C CNN
	1    6900 4500
	0    1    1    0   
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 60F28973
P 6900 4000
AR Path="/6111FD42/60F28973" Ref="#PWR?"  Part="1" 
AR Path="/60F0CD1D/60F28973" Ref="#PWR0179"  Part="1" 
F 0 "#PWR0179" H 6900 3850 50  0001 C CNN
F 1 "+5V" V 6915 4128 50  0000 L CNN
F 2 "" H 6900 4000 50  0001 C CNN
F 3 "" H 6900 4000 50  0001 C CNN
	1    6900 4000
	0    -1   -1   0   
$EndComp
$Comp
L Clockdiv-KiCad-library:SN74AHCT125N U?
U 4 1 60F28979
P 5150 3850
AR Path="/6111FD42/60F28979" Ref="U?"  Part="2" 
AR Path="/60F0CD1D/60F28979" Ref="U13"  Part="4" 
F 0 "U13" H 5350 3750 50  0000 C CNN
F 1 "SN74AHCT125N" H 5500 4000 50  0000 C CNN
F 2 "Package_SO:SO-14_5.3x10.2mm_P1.27mm" H 5150 3850 50  0001 C CNN
F 3 "https://www.ti.com/general/docs/suppproductinfo.tsp?distId=10&gotoUrl=https%3A%2F%2Fwww.ti.com%2Flit%2Fgpn%2Fsn74ahct125" H 5150 3850 50  0001 C CNN
	4    5150 3850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60F2897F
P 4850 3800
AR Path="/6111FD42/60F2897F" Ref="#PWR?"  Part="1" 
AR Path="/60F0CD1D/60F2897F" Ref="#PWR0173"  Part="1" 
F 0 "#PWR0173" H 4850 3550 50  0001 C CNN
F 1 "GND" V 4855 3672 50  0000 R CNN
F 2 "" H 4850 3800 50  0001 C CNN
F 3 "" H 4850 3800 50  0001 C CNN
	1    4850 3800
	0    1    1    0   
$EndComp
Wire Wire Line
	4850 3900 4500 3900
$Comp
L Clockdiv-KiCad-library:SN74HC14S U?
U 2 1 60F28986
P 5450 5250
AR Path="/6111FD42/60F28986" Ref="U?"  Part="1" 
AR Path="/60F0CD1D/60F28986" Ref="U14"  Part="2" 
F 0 "U14" H 5700 5350 50  0000 R CNN
F 1 "SN74HC14S" H 5950 5150 50  0000 R CNN
F 2 "Package_SO:SO-14_5.3x10.2mm_P1.27mm" H 5450 5250 50  0001 C CNN
F 3 "https://www.ti.com/lit/gpn/sn74hc14" H 5450 5250 50  0001 C CNN
	2    5450 5250
	-1   0    0    -1  
$EndComp
Wire Wire Line
	5150 5250 4500 5250
$Comp
L power:GND #PWR?
U 1 1 60F2898D
P 5500 5550
AR Path="/6111FD42/60F2898D" Ref="#PWR?"  Part="1" 
AR Path="/60F0CD1D/60F2898D" Ref="#PWR0175"  Part="1" 
F 0 "#PWR0175" H 5500 5300 50  0001 C CNN
F 1 "GND" H 5450 5500 50  0000 R CNN
F 2 "" H 5500 5550 50  0001 C CNN
F 3 "" H 5500 5550 50  0001 C CNN
	1    5500 5550
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 60F28993
P 5600 4850
AR Path="/6111FD42/60F28993" Ref="#PWR?"  Part="1" 
AR Path="/60F0CD1D/60F28993" Ref="#PWR0176"  Part="1" 
F 0 "#PWR0176" H 5600 4700 50  0001 C CNN
F 1 "+3.3V" V 5600 4950 50  0000 L CNN
F 2 "" H 5600 4850 50  0001 C CNN
F 3 "" H 5600 4850 50  0001 C CNN
	1    5600 4850
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 60F28999
P 6450 5100
AR Path="/6111FD42/60F28999" Ref="R?"  Part="1" 
AR Path="/60F0CD1D/60F28999" Ref="R67"  Part="1" 
F 0 "R67" H 6520 5146 50  0000 L CNN
F 1 "1k" H 6520 5055 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 6380 5100 50  0001 C CNN
F 3 "~" H 6450 5100 50  0001 C CNN
	1    6450 5100
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 60F2899F
P 6050 5100
AR Path="/6111FD42/60F2899F" Ref="R?"  Part="1" 
AR Path="/60F0CD1D/60F2899F" Ref="R66"  Part="1" 
F 0 "R66" H 5980 5054 50  0000 R CNN
F 1 "10k" H 5980 5145 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 5980 5100 50  0001 C CNN
F 3 "~" H 6050 5100 50  0001 C CNN
	1    6050 5100
	-1   0    0    1   
$EndComp
Wire Wire Line
	5750 5250 6050 5250
Connection ~ 6050 5250
$Comp
L Device:C C?
U 1 1 60F289A8
P 6050 5400
AR Path="/6111FD42/60F289A8" Ref="C?"  Part="1" 
AR Path="/60F0CD1D/60F289A8" Ref="C20"  Part="1" 
F 0 "C20" H 6165 5446 50  0000 L CNN
F 1 "0.1uF 16V" H 6165 5355 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 6088 5250 50  0001 C CNN
F 3 "~" H 6050 5400 50  0001 C CNN
	1    6050 5400
	1    0    0    -1  
$EndComp
Wire Wire Line
	5500 5550 6050 5550
Wire Wire Line
	6050 4950 5500 4950
Wire Wire Line
	6050 5250 6450 5250
Wire Wire Line
	5500 4950 5500 4850
Wire Wire Line
	5500 4850 5600 4850
$Comp
L Clockdiv-KiCad-library:SN74AHCT125N U?
U 3 1 60F289C5
P 5150 3300
AR Path="/6111FD42/60F289C5" Ref="U?"  Part="1" 
AR Path="/60F0CD1D/60F289C5" Ref="U13"  Part="3" 
F 0 "U13" H 5250 3200 50  0000 L CNN
F 1 "SN74AHCT125N" H 5200 3450 50  0000 L CNN
F 2 "Package_SO:SO-14_5.3x10.2mm_P1.27mm" H 5150 3300 50  0001 C CNN
F 3 "https://www.ti.com/general/docs/suppproductinfo.tsp?distId=10&gotoUrl=https%3A%2F%2Fwww.ti.com%2Flit%2Fgpn%2Fsn74ahct125" H 5150 3300 50  0001 C CNN
	3    5150 3300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60F289D1
P 4850 3250
AR Path="/6111FD42/60F289D1" Ref="#PWR?"  Part="1" 
AR Path="/60F0CD1D/60F289D1" Ref="#PWR0172"  Part="1" 
F 0 "#PWR0172" H 4850 3000 50  0001 C CNN
F 1 "GND" V 4855 3122 50  0000 R CNN
F 2 "" H 4850 3250 50  0001 C CNN
F 3 "" H 4850 3250 50  0001 C CNN
	1    4850 3250
	0    1    1    0   
$EndComp
Text Label 3650 2850 0    200  ~ 0
STEPPER_MOTOR_CONNECTION_14
Text Notes 6850 3650 2    50   ~ 0
DIR
Text Notes 6500 3800 2    50   ~ 0
STEP
Text Notes 6850 4400 2    50   ~ 0
END 2
Text Notes 6850 4600 2    50   ~ 0
END 1
Wire Wire Line
	6700 3300 6700 3900
Wire Wire Line
	6700 3900 6900 3900
Wire Wire Line
	6450 4600 6900 4600
$Comp
L Connector:Conn_01x02_Male J?
U 1 1 60F289E5
P 5450 4200
AR Path="/6111FD42/60F289E5" Ref="J?"  Part="1" 
AR Path="/60F0CD1D/60F289E5" Ref="J22"  Part="1" 
F 0 "J22" H 5500 4250 25  0000 C CNN
F 1 "Conn_01x02_General Purpose 14" H 5050 4250 25  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 5450 4200 50  0001 C CNN
F 3 "~" H 5450 4200 50  0001 C CNN
	1    5450 4200
	1    0    0    -1  
$EndComp
Wire Wire Line
	5450 3300 6700 3300
Wire Wire Line
	5450 3850 6550 3850
Wire Wire Line
	6550 3850 6550 4100
Wire Wire Line
	6550 4100 6900 4100
Wire Wire Line
	6450 4600 6450 4950
$Comp
L power:GND #PWR?
U 1 1 60F289F0
P 5950 4100
AR Path="/6111FD42/60F289F0" Ref="#PWR?"  Part="1" 
AR Path="/60F0CD1D/60F289F0" Ref="#PWR0177"  Part="1" 
F 0 "#PWR0177" H 5950 3850 50  0001 C CNN
F 1 "GND" V 5950 3950 50  0000 R CNN
F 2 "" H 5950 4100 50  0001 C CNN
F 3 "" H 5950 4100 50  0001 C CNN
	1    5950 4100
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R?
U 1 1 60F289F6
P 5800 4400
AR Path="/6111FD42/60F289F6" Ref="R?"  Part="1" 
AR Path="/60F0CD1D/60F289F6" Ref="R65"  Part="1" 
F 0 "R65" V 5800 4450 50  0000 R CNN
F 1 "10k" V 5730 4445 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 5730 4400 50  0001 C CNN
F 3 "~" H 5800 4400 50  0001 C CNN
	1    5800 4400
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R?
U 1 1 60F289FC
P 5800 4100
AR Path="/6111FD42/60F289FC" Ref="R?"  Part="1" 
AR Path="/60F0CD1D/60F289FC" Ref="R64"  Part="1" 
F 0 "R64" V 5800 4150 50  0000 R CNN
F 1 "10k" V 5900 4150 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 5730 4100 50  0001 C CNN
F 3 "~" H 5800 4100 50  0001 C CNN
	1    5800 4100
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60F28A02
P 5950 4400
AR Path="/6111FD42/60F28A02" Ref="#PWR?"  Part="1" 
AR Path="/60F0CD1D/60F28A02" Ref="#PWR0178"  Part="1" 
F 0 "#PWR0178" H 5950 4150 50  0001 C CNN
F 1 "GND" V 5950 4250 50  0000 R CNN
F 2 "" H 5950 4400 50  0001 C CNN
F 3 "" H 5950 4400 50  0001 C CNN
	1    5950 4400
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5650 4100 5650 4200
Wire Wire Line
	5650 4300 5650 4400
Wire Wire Line
	5650 4200 6900 4200
Connection ~ 5650 4200
Wire Wire Line
	5650 4300 6900 4300
Connection ~ 5650 4300
Wire Wire Line
	6900 4400 6350 4400
Wire Wire Line
	6350 4400 6350 4600
Text Notes 4650 4350 0    25   ~ 0
simply two unused lines from cat cable. \npulled to gnd if unused, otherwise for\nprototyping / testing..
Text HLabel 4500 3350 0    50   Input ~ 0
Stepper_DIR
Wire Wire Line
	4500 3350 4850 3350
Text HLabel 4500 3900 0    50   Input ~ 0
Stepper_STEP
Text HLabel 4500 5250 0    50   Output ~ 0
Stepper_END
Text HLabel 4500 4600 0    50   Output ~ 0
END_ALL
Wire Wire Line
	4500 4600 6350 4600
$EndSCHEMATC
