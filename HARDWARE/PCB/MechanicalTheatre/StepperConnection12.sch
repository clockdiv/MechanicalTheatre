EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 13 15
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
U 4 1 60F1A87D
P 7050 4000
AR Path="/6111FD42/60F1A87D" Ref="J?"  Part="1" 
AR Path="/60F0BCB6/60F1A87D" Ref="J12"  Part="4" 
AR Path="/60F1A87D" Ref="J12"  Part="4" 
F 0 "J12" H 7107 4667 50  0000 C CNN
F 1 "RJ45 8x Socket" H 7107 4576 50  0000 C CNN
F 2 "Clockdiv-KiCad:RJ45_Conrad_8x" V 7050 4025 50  0001 C CNN
F 3 "~" V 7050 4025 50  0001 C CNN
	4    7050 4000
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60F1A883
P 6650 4300
AR Path="/6111FD42/60F1A883" Ref="#PWR?"  Part="1" 
AR Path="/60F0BCB6/60F1A883" Ref="#PWR0160"  Part="1" 
F 0 "#PWR0160" H 6650 4050 50  0001 C CNN
F 1 "GND" V 6650 4200 50  0000 R CNN
F 2 "" H 6650 4300 50  0001 C CNN
F 3 "" H 6650 4300 50  0001 C CNN
	1    6650 4300
	0    1    1    0   
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 60F1A889
P 6650 3800
AR Path="/6111FD42/60F1A889" Ref="#PWR?"  Part="1" 
AR Path="/60F0BCB6/60F1A889" Ref="#PWR0159"  Part="1" 
F 0 "#PWR0159" H 6650 3650 50  0001 C CNN
F 1 "+5V" V 6665 3928 50  0000 L CNN
F 2 "" H 6650 3800 50  0001 C CNN
F 3 "" H 6650 3800 50  0001 C CNN
	1    6650 3800
	0    -1   -1   0   
$EndComp
$Comp
L Clockdiv-KiCad-library:SN74AHCT125N U?
U 4 1 60F1A88F
P 4900 3650
AR Path="/6111FD42/60F1A88F" Ref="U?"  Part="2" 
AR Path="/60F0BCB6/60F1A88F" Ref="U12"  Part="4" 
F 0 "U12" H 5100 3550 50  0000 C CNN
F 1 "SN74AHCT125N" H 5250 3800 50  0000 C CNN
F 2 "Package_SO:SO-14_5.3x10.2mm_P1.27mm" H 4900 3650 50  0001 C CNN
F 3 "https://www.ti.com/general/docs/suppproductinfo.tsp?distId=10&gotoUrl=https%3A%2F%2Fwww.ti.com%2Flit%2Fgpn%2Fsn74ahct125" H 4900 3650 50  0001 C CNN
	4    4900 3650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60F1A895
P 4600 3600
AR Path="/6111FD42/60F1A895" Ref="#PWR?"  Part="1" 
AR Path="/60F0BCB6/60F1A895" Ref="#PWR0152"  Part="1" 
F 0 "#PWR0152" H 4600 3350 50  0001 C CNN
F 1 "GND" V 4605 3472 50  0000 R CNN
F 2 "" H 4600 3600 50  0001 C CNN
F 3 "" H 4600 3600 50  0001 C CNN
	1    4600 3600
	0    1    1    0   
$EndComp
Wire Wire Line
	4600 3700 4250 3700
$Comp
L Clockdiv-KiCad-library:SN74HC14S U?
U 6 1 60F1A89C
P 5200 5050
AR Path="/6111FD42/60F1A89C" Ref="U?"  Part="1" 
AR Path="/60F0BCB6/60F1A89C" Ref="U10"  Part="6" 
F 0 "U10" H 5450 5150 50  0000 R CNN
F 1 "SN74HC14S" H 5700 4950 50  0000 R CNN
F 2 "Package_SO:SO-14_5.3x10.2mm_P1.27mm" H 5200 5050 50  0001 C CNN
F 3 "https://www.ti.com/lit/gpn/sn74hc14" H 5200 5050 50  0001 C CNN
	6    5200 5050
	-1   0    0    -1  
$EndComp
Wire Wire Line
	4900 5050 4250 5050
$Comp
L power:GND #PWR?
U 1 1 60F1A8A3
P 5250 5350
AR Path="/6111FD42/60F1A8A3" Ref="#PWR?"  Part="1" 
AR Path="/60F0BCB6/60F1A8A3" Ref="#PWR0155"  Part="1" 
F 0 "#PWR0155" H 5250 5100 50  0001 C CNN
F 1 "GND" H 5200 5300 50  0000 R CNN
F 2 "" H 5250 5350 50  0001 C CNN
F 3 "" H 5250 5350 50  0001 C CNN
	1    5250 5350
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 60F1A8A9
P 5350 4650
AR Path="/6111FD42/60F1A8A9" Ref="#PWR?"  Part="1" 
AR Path="/60F0BCB6/60F1A8A9" Ref="#PWR0156"  Part="1" 
F 0 "#PWR0156" H 5350 4500 50  0001 C CNN
F 1 "+3.3V" V 5350 4750 50  0000 L CNN
F 2 "" H 5350 4650 50  0001 C CNN
F 3 "" H 5350 4650 50  0001 C CNN
	1    5350 4650
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 60F1A8AF
P 6200 4900
AR Path="/6111FD42/60F1A8AF" Ref="R?"  Part="1" 
AR Path="/60F0BCB6/60F1A8AF" Ref="R59"  Part="1" 
F 0 "R59" H 6270 4946 50  0000 L CNN
F 1 "1k" H 6270 4855 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 6130 4900 50  0001 C CNN
F 3 "~" H 6200 4900 50  0001 C CNN
	1    6200 4900
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 60F1A8B5
P 5800 4900
AR Path="/6111FD42/60F1A8B5" Ref="R?"  Part="1" 
AR Path="/60F0BCB6/60F1A8B5" Ref="R58"  Part="1" 
F 0 "R58" H 5730 4854 50  0000 R CNN
F 1 "10k" H 5730 4945 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 5730 4900 50  0001 C CNN
F 3 "~" H 5800 4900 50  0001 C CNN
	1    5800 4900
	-1   0    0    1   
$EndComp
Wire Wire Line
	5500 5050 5800 5050
Connection ~ 5800 5050
$Comp
L Device:C C?
U 1 1 60F1A8BE
P 5800 5200
AR Path="/6111FD42/60F1A8BE" Ref="C?"  Part="1" 
AR Path="/60F0BCB6/60F1A8BE" Ref="C16"  Part="1" 
F 0 "C16" H 5915 5246 50  0000 L CNN
F 1 "0.1uF 16V" H 5915 5155 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 5838 5050 50  0001 C CNN
F 3 "~" H 5800 5200 50  0001 C CNN
	1    5800 5200
	1    0    0    -1  
$EndComp
Wire Wire Line
	5250 5350 5800 5350
Wire Wire Line
	5800 4750 5250 4750
Wire Wire Line
	5800 5050 6200 5050
Wire Wire Line
	5250 4750 5250 4650
Wire Wire Line
	5250 4650 5350 4650
$Comp
L Clockdiv-KiCad-library:SN74AHCT125N U?
U 3 1 60F1A8DB
P 4900 3100
AR Path="/6111FD42/60F1A8DB" Ref="U?"  Part="1" 
AR Path="/60F0BCB6/60F1A8DB" Ref="U12"  Part="3" 
F 0 "U12" H 5000 3000 50  0000 L CNN
F 1 "SN74AHCT125N" H 4950 3250 50  0000 L CNN
F 2 "Package_SO:SO-14_5.3x10.2mm_P1.27mm" H 4900 3100 50  0001 C CNN
F 3 "https://www.ti.com/general/docs/suppproductinfo.tsp?distId=10&gotoUrl=https%3A%2F%2Fwww.ti.com%2Flit%2Fgpn%2Fsn74ahct125" H 4900 3100 50  0001 C CNN
	3    4900 3100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60F1A8E7
P 4600 3050
AR Path="/6111FD42/60F1A8E7" Ref="#PWR?"  Part="1" 
AR Path="/60F0BCB6/60F1A8E7" Ref="#PWR0151"  Part="1" 
F 0 "#PWR0151" H 4600 2800 50  0001 C CNN
F 1 "GND" V 4605 2922 50  0000 R CNN
F 2 "" H 4600 3050 50  0001 C CNN
F 3 "" H 4600 3050 50  0001 C CNN
	1    4600 3050
	0    1    1    0   
$EndComp
Text Label 3400 2650 0    200  ~ 0
STEPPER_MOTOR_CONNECTION_12
Text Notes 6600 3450 2    50   ~ 0
DIR
Text Notes 6250 3600 2    50   ~ 0
STEP
Text Notes 6600 4200 2    50   ~ 0
END 2
Text Notes 6600 4400 2    50   ~ 0
END 1
Wire Wire Line
	6450 3100 6450 3700
Wire Wire Line
	6450 3700 6650 3700
Wire Wire Line
	6200 4400 6650 4400
$Comp
L Connector:Conn_01x02_Male J?
U 1 1 60F1A8FB
P 5200 4000
AR Path="/6111FD42/60F1A8FB" Ref="J?"  Part="1" 
AR Path="/60F0BCB6/60F1A8FB" Ref="J20"  Part="1" 
F 0 "J20" H 5250 4050 25  0000 C CNN
F 1 "Conn_01x02_General Purpose 12" H 4800 4050 25  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 5200 4000 50  0001 C CNN
F 3 "~" H 5200 4000 50  0001 C CNN
	1    5200 4000
	1    0    0    -1  
$EndComp
Wire Wire Line
	5200 3100 6450 3100
Wire Wire Line
	5200 3650 6300 3650
Wire Wire Line
	6300 3650 6300 3900
Wire Wire Line
	6300 3900 6650 3900
Wire Wire Line
	6200 4400 6200 4750
$Comp
L power:GND #PWR?
U 1 1 60F1A906
P 5700 3900
AR Path="/6111FD42/60F1A906" Ref="#PWR?"  Part="1" 
AR Path="/60F0BCB6/60F1A906" Ref="#PWR0157"  Part="1" 
F 0 "#PWR0157" H 5700 3650 50  0001 C CNN
F 1 "GND" V 5700 3750 50  0000 R CNN
F 2 "" H 5700 3900 50  0001 C CNN
F 3 "" H 5700 3900 50  0001 C CNN
	1    5700 3900
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R?
U 1 1 60F1A90C
P 5550 4200
AR Path="/6111FD42/60F1A90C" Ref="R?"  Part="1" 
AR Path="/60F0BCB6/60F1A90C" Ref="R57"  Part="1" 
F 0 "R57" V 5550 4250 50  0000 R CNN
F 1 "10k" V 5480 4245 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 5480 4200 50  0001 C CNN
F 3 "~" H 5550 4200 50  0001 C CNN
	1    5550 4200
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R?
U 1 1 60F1A912
P 5550 3900
AR Path="/6111FD42/60F1A912" Ref="R?"  Part="1" 
AR Path="/60F0BCB6/60F1A912" Ref="R56"  Part="1" 
F 0 "R56" V 5550 3950 50  0000 R CNN
F 1 "10k" V 5650 3950 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 5480 3900 50  0001 C CNN
F 3 "~" H 5550 3900 50  0001 C CNN
	1    5550 3900
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60F1A918
P 5700 4200
AR Path="/6111FD42/60F1A918" Ref="#PWR?"  Part="1" 
AR Path="/60F0BCB6/60F1A918" Ref="#PWR0158"  Part="1" 
F 0 "#PWR0158" H 5700 3950 50  0001 C CNN
F 1 "GND" V 5700 4050 50  0000 R CNN
F 2 "" H 5700 4200 50  0001 C CNN
F 3 "" H 5700 4200 50  0001 C CNN
	1    5700 4200
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5400 3900 5400 4000
Wire Wire Line
	5400 4100 5400 4200
Wire Wire Line
	5400 4000 6650 4000
Connection ~ 5400 4000
Wire Wire Line
	5400 4100 6650 4100
Connection ~ 5400 4100
Wire Wire Line
	6650 4200 6100 4200
Wire Wire Line
	6100 4200 6100 4400
Text Notes 4400 4150 0    25   ~ 0
simply two unused lines from cat cable. \npulled to gnd if unused, otherwise for\nprototyping / testing..
Text HLabel 4250 3150 0    50   Input ~ 0
Stepper_DIR
Wire Wire Line
	4250 3150 4600 3150
Text HLabel 4250 3700 0    50   Input ~ 0
Stepper_STEP
Text HLabel 4250 5050 0    50   Output ~ 0
Stepper_END
Text HLabel 4250 4400 0    50   Output ~ 0
END_ALL
Wire Wire Line
	4250 4400 6100 4400
$EndSCHEMATC
