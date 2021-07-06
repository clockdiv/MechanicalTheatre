EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 12 15
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
U 3 1 60F11680
P 7500 4250
AR Path="/6111FD42/60F11680" Ref="J?"  Part="1" 
AR Path="/60EB8ABE/60F11680" Ref="J12"  Part="3" 
F 0 "J12" H 7557 4917 50  0000 C CNN
F 1 "RJ45 8x Socket" H 7557 4826 50  0000 C CNN
F 2 "Clockdiv-KiCad:RJ45_Conrad_8x" V 7500 4275 50  0001 C CNN
F 3 "~" V 7500 4275 50  0001 C CNN
	3    7500 4250
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60F11686
P 7100 4550
AR Path="/6111FD42/60F11686" Ref="#PWR?"  Part="1" 
AR Path="/60EB8ABE/60F11686" Ref="#PWR0150"  Part="1" 
F 0 "#PWR0150" H 7100 4300 50  0001 C CNN
F 1 "GND" V 7100 4450 50  0000 R CNN
F 2 "" H 7100 4550 50  0001 C CNN
F 3 "" H 7100 4550 50  0001 C CNN
	1    7100 4550
	0    1    1    0   
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 60F1168C
P 7100 4050
AR Path="/6111FD42/60F1168C" Ref="#PWR?"  Part="1" 
AR Path="/60EB8ABE/60F1168C" Ref="#PWR0149"  Part="1" 
F 0 "#PWR0149" H 7100 3900 50  0001 C CNN
F 1 "+5V" V 7115 4178 50  0000 L CNN
F 2 "" H 7100 4050 50  0001 C CNN
F 3 "" H 7100 4050 50  0001 C CNN
	1    7100 4050
	0    -1   -1   0   
$EndComp
$Comp
L Clockdiv-KiCad-library:SN74AHCT125N U?
U 2 1 60F11692
P 5350 3900
AR Path="/6111FD42/60F11692" Ref="U?"  Part="2" 
AR Path="/60EB8ABE/60F11692" Ref="U12"  Part="2" 
F 0 "U12" H 5550 3800 50  0000 C CNN
F 1 "SN74AHCT125N" H 5700 4050 50  0000 C CNN
F 2 "Package_SO:SO-14_5.3x10.2mm_P1.27mm" H 5350 3900 50  0001 C CNN
F 3 "https://www.ti.com/general/docs/suppproductinfo.tsp?distId=10&gotoUrl=https%3A%2F%2Fwww.ti.com%2Flit%2Fgpn%2Fsn74ahct125" H 5350 3900 50  0001 C CNN
	2    5350 3900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60F11698
P 5050 3850
AR Path="/6111FD42/60F11698" Ref="#PWR?"  Part="1" 
AR Path="/60EB8ABE/60F11698" Ref="#PWR0142"  Part="1" 
F 0 "#PWR0142" H 5050 3600 50  0001 C CNN
F 1 "GND" V 5055 3722 50  0000 R CNN
F 2 "" H 5050 3850 50  0001 C CNN
F 3 "" H 5050 3850 50  0001 C CNN
	1    5050 3850
	0    1    1    0   
$EndComp
Wire Wire Line
	5050 3950 4700 3950
$Comp
L Clockdiv-KiCad-library:SN74HC14S U?
U 5 1 60F1169F
P 5650 5300
AR Path="/6111FD42/60F1169F" Ref="U?"  Part="1" 
AR Path="/60EB8ABE/60F1169F" Ref="U10"  Part="5" 
F 0 "U10" H 5900 5400 50  0000 R CNN
F 1 "SN74HC14S" H 6150 5200 50  0000 R CNN
F 2 "Package_SO:SO-14_5.3x10.2mm_P1.27mm" H 5650 5300 50  0001 C CNN
F 3 "https://www.ti.com/lit/gpn/sn74hc14" H 5650 5300 50  0001 C CNN
	5    5650 5300
	-1   0    0    -1  
$EndComp
Wire Wire Line
	5350 5300 4700 5300
$Comp
L power:GND #PWR?
U 1 1 60F116A6
P 5700 5600
AR Path="/6111FD42/60F116A6" Ref="#PWR?"  Part="1" 
AR Path="/60EB8ABE/60F116A6" Ref="#PWR0145"  Part="1" 
F 0 "#PWR0145" H 5700 5350 50  0001 C CNN
F 1 "GND" H 5650 5550 50  0000 R CNN
F 2 "" H 5700 5600 50  0001 C CNN
F 3 "" H 5700 5600 50  0001 C CNN
	1    5700 5600
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 60F116AC
P 5800 4900
AR Path="/6111FD42/60F116AC" Ref="#PWR?"  Part="1" 
AR Path="/60EB8ABE/60F116AC" Ref="#PWR0146"  Part="1" 
F 0 "#PWR0146" H 5800 4750 50  0001 C CNN
F 1 "+3.3V" V 5800 5000 50  0000 L CNN
F 2 "" H 5800 4900 50  0001 C CNN
F 3 "" H 5800 4900 50  0001 C CNN
	1    5800 4900
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 60F116B2
P 6650 5150
AR Path="/6111FD42/60F116B2" Ref="R?"  Part="1" 
AR Path="/60EB8ABE/60F116B2" Ref="R55"  Part="1" 
F 0 "R55" H 6720 5196 50  0000 L CNN
F 1 "1k" H 6720 5105 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 6580 5150 50  0001 C CNN
F 3 "~" H 6650 5150 50  0001 C CNN
	1    6650 5150
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 60F116B8
P 6250 5150
AR Path="/6111FD42/60F116B8" Ref="R?"  Part="1" 
AR Path="/60EB8ABE/60F116B8" Ref="R54"  Part="1" 
F 0 "R54" H 6180 5104 50  0000 R CNN
F 1 "10k" H 6180 5195 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 6180 5150 50  0001 C CNN
F 3 "~" H 6250 5150 50  0001 C CNN
	1    6250 5150
	-1   0    0    1   
$EndComp
Wire Wire Line
	5950 5300 6250 5300
Connection ~ 6250 5300
$Comp
L Device:C C?
U 1 1 60F116C1
P 6250 5450
AR Path="/6111FD42/60F116C1" Ref="C?"  Part="1" 
AR Path="/60EB8ABE/60F116C1" Ref="C15"  Part="1" 
F 0 "C15" H 6365 5496 50  0000 L CNN
F 1 "0.1uF 16V" H 6365 5405 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 6288 5300 50  0001 C CNN
F 3 "~" H 6250 5450 50  0001 C CNN
	1    6250 5450
	1    0    0    -1  
$EndComp
Wire Wire Line
	5700 5600 6250 5600
Wire Wire Line
	6250 5000 5700 5000
Wire Wire Line
	6250 5300 6650 5300
Wire Wire Line
	5700 5000 5700 4900
Wire Wire Line
	5700 4900 5800 4900
$Comp
L Clockdiv-KiCad-library:SN74AHCT125N U?
U 1 1 60F116DE
P 5350 3350
AR Path="/6111FD42/60F116DE" Ref="U?"  Part="1" 
AR Path="/60EB8ABE/60F116DE" Ref="U12"  Part="1" 
F 0 "U12" H 5450 3250 50  0000 L CNN
F 1 "SN74AHCT125N" H 5400 3500 50  0000 L CNN
F 2 "Package_SO:SO-14_5.3x10.2mm_P1.27mm" H 5350 3350 50  0001 C CNN
F 3 "https://www.ti.com/general/docs/suppproductinfo.tsp?distId=10&gotoUrl=https%3A%2F%2Fwww.ti.com%2Flit%2Fgpn%2Fsn74ahct125" H 5350 3350 50  0001 C CNN
	1    5350 3350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60F116E4
P 5300 3550
AR Path="/6111FD42/60F116E4" Ref="#PWR?"  Part="1" 
AR Path="/60EB8ABE/60F116E4" Ref="#PWR0144"  Part="1" 
F 0 "#PWR0144" H 5300 3300 50  0001 C CNN
F 1 "GND" H 5250 3500 50  0000 R CNN
F 2 "" H 5300 3550 50  0001 C CNN
F 3 "" H 5300 3550 50  0001 C CNN
	1    5300 3550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60F116EA
P 5050 3300
AR Path="/6111FD42/60F116EA" Ref="#PWR?"  Part="1" 
AR Path="/60EB8ABE/60F116EA" Ref="#PWR0141"  Part="1" 
F 0 "#PWR0141" H 5050 3050 50  0001 C CNN
F 1 "GND" V 5055 3172 50  0000 R CNN
F 2 "" H 5050 3300 50  0001 C CNN
F 3 "" H 5050 3300 50  0001 C CNN
	1    5050 3300
	0    1    1    0   
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 60F116F0
P 5300 3150
AR Path="/6111FD42/60F116F0" Ref="#PWR?"  Part="1" 
AR Path="/60EB8ABE/60F116F0" Ref="#PWR0143"  Part="1" 
F 0 "#PWR0143" H 5300 3000 50  0001 C CNN
F 1 "+5V" H 5100 3200 50  0000 L CNN
F 2 "" H 5300 3150 50  0001 C CNN
F 3 "" H 5300 3150 50  0001 C CNN
	1    5300 3150
	1    0    0    -1  
$EndComp
Text Label 3850 2900 0    200  ~ 0
STEPPER_MOTOR_CONNECTION_11
Text Notes 7050 3700 2    50   ~ 0
DIR
Text Notes 6700 3850 2    50   ~ 0
STEP
Text Notes 7050 4450 2    50   ~ 0
END 2
Text Notes 7050 4650 2    50   ~ 0
END 1
Wire Wire Line
	6900 3350 6900 3950
Wire Wire Line
	6900 3950 7100 3950
Wire Wire Line
	6650 4650 7100 4650
$Comp
L Connector:Conn_01x02_Male J?
U 1 1 60F116FE
P 5650 4250
AR Path="/6111FD42/60F116FE" Ref="J?"  Part="1" 
AR Path="/60EB8ABE/60F116FE" Ref="J19"  Part="1" 
F 0 "J19" H 5700 4300 25  0000 C CNN
F 1 "Conn_01x02_General Purpose 11" H 5250 4300 25  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 5650 4250 50  0001 C CNN
F 3 "~" H 5650 4250 50  0001 C CNN
	1    5650 4250
	1    0    0    -1  
$EndComp
Wire Wire Line
	5650 3350 6900 3350
Wire Wire Line
	5650 3900 6750 3900
Wire Wire Line
	6750 3900 6750 4150
Wire Wire Line
	6750 4150 7100 4150
Wire Wire Line
	6650 4650 6650 5000
$Comp
L power:GND #PWR?
U 1 1 60F11709
P 6150 4150
AR Path="/6111FD42/60F11709" Ref="#PWR?"  Part="1" 
AR Path="/60EB8ABE/60F11709" Ref="#PWR0147"  Part="1" 
F 0 "#PWR0147" H 6150 3900 50  0001 C CNN
F 1 "GND" V 6150 4000 50  0000 R CNN
F 2 "" H 6150 4150 50  0001 C CNN
F 3 "" H 6150 4150 50  0001 C CNN
	1    6150 4150
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R?
U 1 1 60F1170F
P 6000 4450
AR Path="/6111FD42/60F1170F" Ref="R?"  Part="1" 
AR Path="/60EB8ABE/60F1170F" Ref="R53"  Part="1" 
F 0 "R53" V 6000 4500 50  0000 R CNN
F 1 "10k" V 5930 4495 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 5930 4450 50  0001 C CNN
F 3 "~" H 6000 4450 50  0001 C CNN
	1    6000 4450
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R?
U 1 1 60F11715
P 6000 4150
AR Path="/6111FD42/60F11715" Ref="R?"  Part="1" 
AR Path="/60EB8ABE/60F11715" Ref="R52"  Part="1" 
F 0 "R52" V 6000 4200 50  0000 R CNN
F 1 "10k" V 6100 4200 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 5930 4150 50  0001 C CNN
F 3 "~" H 6000 4150 50  0001 C CNN
	1    6000 4150
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60F1171B
P 6150 4450
AR Path="/6111FD42/60F1171B" Ref="#PWR?"  Part="1" 
AR Path="/60EB8ABE/60F1171B" Ref="#PWR0148"  Part="1" 
F 0 "#PWR0148" H 6150 4200 50  0001 C CNN
F 1 "GND" V 6150 4300 50  0000 R CNN
F 2 "" H 6150 4450 50  0001 C CNN
F 3 "" H 6150 4450 50  0001 C CNN
	1    6150 4450
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5850 4150 5850 4250
Wire Wire Line
	5850 4350 5850 4450
Wire Wire Line
	5850 4250 7100 4250
Connection ~ 5850 4250
Wire Wire Line
	5850 4350 7100 4350
Connection ~ 5850 4350
Wire Wire Line
	7100 4450 6550 4450
Wire Wire Line
	6550 4450 6550 4650
Text Notes 4850 4400 0    25   ~ 0
simply two unused lines from cat cable. \npulled to gnd if unused, otherwise for\nprototyping / testing..
Text HLabel 4700 3400 0    50   Input ~ 0
Stepper_DIR
Wire Wire Line
	4700 3400 5050 3400
Text HLabel 4700 3950 0    50   Input ~ 0
Stepper_STEP
Text HLabel 4700 5300 0    50   Output ~ 0
Stepper_END
Text HLabel 4700 4650 0    50   Output ~ 0
END_ALL
Wire Wire Line
	4700 4650 6550 4650
$EndSCHEMATC
