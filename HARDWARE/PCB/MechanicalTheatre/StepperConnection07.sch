EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 8 15
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
U 7 1 60D803B6
P 7450 3850
AR Path="/6111FD42/60D803B6" Ref="J?"  Part="1" 
AR Path="/60D6E535/60D803B6" Ref="J11"  Part="7" 
AR Path="/60D803B6" Ref="J11"  Part="7" 
F 0 "J11" H 7507 4517 50  0000 C CNN
F 1 "RJ45 8x Socket" H 7507 4426 50  0000 C CNN
F 2 "Clockdiv-KiCad:RJ45_Conrad_8x" V 7450 3875 50  0001 C CNN
F 3 "~" V 7450 3875 50  0001 C CNN
	7    7450 3850
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60D803BC
P 7050 4150
AR Path="/6111FD42/60D803BC" Ref="#PWR?"  Part="1" 
AR Path="/60D6E535/60D803BC" Ref="#PWR0114"  Part="1" 
F 0 "#PWR0114" H 7050 3900 50  0001 C CNN
F 1 "GND" V 7050 4050 50  0000 R CNN
F 2 "" H 7050 4150 50  0001 C CNN
F 3 "" H 7050 4150 50  0001 C CNN
	1    7050 4150
	0    1    1    0   
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 60D803C2
P 7050 3650
AR Path="/6111FD42/60D803C2" Ref="#PWR?"  Part="1" 
AR Path="/60D6E535/60D803C2" Ref="#PWR0113"  Part="1" 
F 0 "#PWR0113" H 7050 3500 50  0001 C CNN
F 1 "+5V" V 7065 3778 50  0000 L CNN
F 2 "" H 7050 3650 50  0001 C CNN
F 3 "" H 7050 3650 50  0001 C CNN
	1    7050 3650
	0    -1   -1   0   
$EndComp
$Comp
L Clockdiv-KiCad-library:SN74AHCT125N U?
U 2 1 60D803C8
P 5300 3500
AR Path="/6111FD42/60D803C8" Ref="U?"  Part="2" 
AR Path="/60D6E535/60D803C8" Ref="U9"  Part="2" 
F 0 "U9" H 5500 3400 50  0000 C CNN
F 1 "SN74AHCT125N" H 5650 3650 50  0000 C CNN
F 2 "Package_SO:SO-14_5.3x10.2mm_P1.27mm" H 5300 3500 50  0001 C CNN
F 3 "https://www.ti.com/general/docs/suppproductinfo.tsp?distId=10&gotoUrl=https%3A%2F%2Fwww.ti.com%2Flit%2Fgpn%2Fsn74ahct125" H 5300 3500 50  0001 C CNN
	2    5300 3500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60D803CE
P 5000 3450
AR Path="/6111FD42/60D803CE" Ref="#PWR?"  Part="1" 
AR Path="/60D6E535/60D803CE" Ref="#PWR0105"  Part="1" 
F 0 "#PWR0105" H 5000 3200 50  0001 C CNN
F 1 "GND" V 5005 3322 50  0000 R CNN
F 2 "" H 5000 3450 50  0001 C CNN
F 3 "" H 5000 3450 50  0001 C CNN
	1    5000 3450
	0    1    1    0   
$EndComp
Wire Wire Line
	5000 3550 4650 3550
$Comp
L Clockdiv-KiCad-library:SN74HC14S U?
U 1 1 60D803D5
P 5600 4900
AR Path="/6111FD42/60D803D5" Ref="U?"  Part="1" 
AR Path="/60D6E535/60D803D5" Ref="U10"  Part="1" 
F 0 "U10" H 5850 5000 50  0000 R CNN
F 1 "SN74HC14S" H 6100 4800 50  0000 R CNN
F 2 "Package_SO:SO-14_5.3x10.2mm_P1.27mm" H 5600 4900 50  0001 C CNN
F 3 "https://www.ti.com/lit/gpn/sn74hc14" H 5600 4900 50  0001 C CNN
	1    5600 4900
	-1   0    0    -1  
$EndComp
Wire Wire Line
	5300 4900 4650 4900
$Comp
L power:GND #PWR?
U 1 1 60D803DC
P 5650 5200
AR Path="/6111FD42/60D803DC" Ref="#PWR?"  Part="1" 
AR Path="/60D6E535/60D803DC" Ref="#PWR0109"  Part="1" 
F 0 "#PWR0109" H 5650 4950 50  0001 C CNN
F 1 "GND" H 5600 5150 50  0000 R CNN
F 2 "" H 5650 5200 50  0001 C CNN
F 3 "" H 5650 5200 50  0001 C CNN
	1    5650 5200
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 60D803E2
P 5750 4500
AR Path="/6111FD42/60D803E2" Ref="#PWR?"  Part="1" 
AR Path="/60D6E535/60D803E2" Ref="#PWR0110"  Part="1" 
F 0 "#PWR0110" H 5750 4350 50  0001 C CNN
F 1 "+3.3V" V 5750 4600 50  0000 L CNN
F 2 "" H 5750 4500 50  0001 C CNN
F 3 "" H 5750 4500 50  0001 C CNN
	1    5750 4500
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 60D803E8
P 6600 4750
AR Path="/6111FD42/60D803E8" Ref="R?"  Part="1" 
AR Path="/60D6E535/60D803E8" Ref="R39"  Part="1" 
F 0 "R39" H 6670 4796 50  0000 L CNN
F 1 "1k" H 6670 4705 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 6530 4750 50  0001 C CNN
F 3 "~" H 6600 4750 50  0001 C CNN
	1    6600 4750
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 60D803EE
P 6200 4750
AR Path="/6111FD42/60D803EE" Ref="R?"  Part="1" 
AR Path="/60D6E535/60D803EE" Ref="R38"  Part="1" 
F 0 "R38" H 6130 4704 50  0000 R CNN
F 1 "10k" H 6130 4795 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 6130 4750 50  0001 C CNN
F 3 "~" H 6200 4750 50  0001 C CNN
	1    6200 4750
	-1   0    0    1   
$EndComp
Wire Wire Line
	5900 4900 6200 4900
Connection ~ 6200 4900
Wire Wire Line
	5650 4700 5650 4600
$Comp
L Device:C C?
U 1 1 60D803F7
P 6200 5050
AR Path="/6111FD42/60D803F7" Ref="C?"  Part="1" 
AR Path="/60D6E535/60D803F7" Ref="C11"  Part="1" 
F 0 "C11" H 6315 5096 50  0000 L CNN
F 1 "0.1uF 16V" H 6315 5005 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 6238 4900 50  0001 C CNN
F 3 "~" H 6200 5050 50  0001 C CNN
	1    6200 5050
	1    0    0    -1  
$EndComp
Wire Wire Line
	5650 5200 5650 5100
Wire Wire Line
	5650 5200 6200 5200
Connection ~ 5650 5200
Wire Wire Line
	6200 4600 5650 4600
Wire Wire Line
	6200 4900 6600 4900
$Comp
L power:GND #PWR?
U 1 1 60D80402
P 5150 4500
AR Path="/6111FD42/60D80402" Ref="#PWR?"  Part="1" 
AR Path="/60D6E535/60D80402" Ref="#PWR0106"  Part="1" 
F 0 "#PWR0106" H 5150 4250 50  0001 C CNN
F 1 "GND" V 5150 4400 50  0000 R CNN
F 2 "" H 5150 4500 50  0001 C CNN
F 3 "" H 5150 4500 50  0001 C CNN
	1    5150 4500
	0    1    1    0   
$EndComp
Wire Wire Line
	5650 4600 5650 4500
Connection ~ 5650 4600
Connection ~ 5650 4500
Wire Wire Line
	5650 4500 5750 4500
Wire Wire Line
	5150 4500 5350 4500
$Comp
L Device:C C?
U 1 1 60D8040E
P 5500 4500
AR Path="/6111FD42/60D8040E" Ref="C?"  Part="1" 
AR Path="/60D6E535/60D8040E" Ref="C10"  Part="1" 
F 0 "C10" V 5450 4550 50  0000 L CNN
F 1 "0.1uF 16V " V 5600 4300 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 5538 4350 50  0001 C CNN
F 3 "~" H 5500 4500 50  0001 C CNN
F 4 "place near SN74HC14s" V 5600 3900 50  0000 C CNN "Comment"
	1    5500 4500
	0    -1   -1   0   
$EndComp
$Comp
L Clockdiv-KiCad-library:SN74AHCT125N U?
U 1 1 60D80414
P 5300 2950
AR Path="/6111FD42/60D80414" Ref="U?"  Part="1" 
AR Path="/60D6E535/60D80414" Ref="U9"  Part="1" 
F 0 "U9" H 5400 2850 50  0000 L CNN
F 1 "SN74AHCT125N" H 5350 3100 50  0000 L CNN
F 2 "Package_SO:SO-14_5.3x10.2mm_P1.27mm" H 5300 2950 50  0001 C CNN
F 3 "https://www.ti.com/general/docs/suppproductinfo.tsp?distId=10&gotoUrl=https%3A%2F%2Fwww.ti.com%2Flit%2Fgpn%2Fsn74ahct125" H 5300 2950 50  0001 C CNN
	1    5300 2950
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60D8041A
P 5250 3150
AR Path="/6111FD42/60D8041A" Ref="#PWR?"  Part="1" 
AR Path="/60D6E535/60D8041A" Ref="#PWR0108"  Part="1" 
F 0 "#PWR0108" H 5250 2900 50  0001 C CNN
F 1 "GND" H 5200 3100 50  0000 R CNN
F 2 "" H 5250 3150 50  0001 C CNN
F 3 "" H 5250 3150 50  0001 C CNN
	1    5250 3150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60D80420
P 5000 2900
AR Path="/6111FD42/60D80420" Ref="#PWR?"  Part="1" 
AR Path="/60D6E535/60D80420" Ref="#PWR0104"  Part="1" 
F 0 "#PWR0104" H 5000 2650 50  0001 C CNN
F 1 "GND" V 5005 2772 50  0000 R CNN
F 2 "" H 5000 2900 50  0001 C CNN
F 3 "" H 5000 2900 50  0001 C CNN
	1    5000 2900
	0    1    1    0   
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 60D80426
P 5250 2750
AR Path="/6111FD42/60D80426" Ref="#PWR?"  Part="1" 
AR Path="/60D6E535/60D80426" Ref="#PWR0107"  Part="1" 
F 0 "#PWR0107" H 5250 2600 50  0001 C CNN
F 1 "+5V" H 5050 2800 50  0000 L CNN
F 2 "" H 5250 2750 50  0001 C CNN
F 3 "" H 5250 2750 50  0001 C CNN
	1    5250 2750
	1    0    0    -1  
$EndComp
Text Label 3800 2500 0    200  ~ 0
STEPPER_MOTOR_CONNECTION_7
Text Notes 7000 3300 2    50   ~ 0
DIR
Text Notes 6650 3450 2    50   ~ 0
STEP
Text Notes 7000 4050 2    50   ~ 0
END 2
Text Notes 7000 4250 2    50   ~ 0
END 1
Wire Wire Line
	6850 2950 6850 3550
Wire Wire Line
	6850 3550 7050 3550
Wire Wire Line
	6600 4250 7050 4250
$Comp
L Connector:Conn_01x02_Male J?
U 1 1 60D80434
P 5600 3850
AR Path="/6111FD42/60D80434" Ref="J?"  Part="1" 
AR Path="/60D6E535/60D80434" Ref="J15"  Part="1" 
F 0 "J15" H 5650 3900 25  0000 C CNN
F 1 "Conn_01x02_General Purpose 07" H 5200 3900 25  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 5600 3850 50  0001 C CNN
F 3 "~" H 5600 3850 50  0001 C CNN
	1    5600 3850
	1    0    0    -1  
$EndComp
Wire Wire Line
	5600 2950 6850 2950
Wire Wire Line
	5600 3500 6700 3500
Wire Wire Line
	6700 3500 6700 3750
Wire Wire Line
	6700 3750 7050 3750
Wire Wire Line
	6600 4250 6600 4600
$Comp
L power:GND #PWR?
U 1 1 60D8043F
P 6100 3750
AR Path="/6111FD42/60D8043F" Ref="#PWR?"  Part="1" 
AR Path="/60D6E535/60D8043F" Ref="#PWR0111"  Part="1" 
F 0 "#PWR0111" H 6100 3500 50  0001 C CNN
F 1 "GND" V 6100 3600 50  0000 R CNN
F 2 "" H 6100 3750 50  0001 C CNN
F 3 "" H 6100 3750 50  0001 C CNN
	1    6100 3750
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R?
U 1 1 60D80445
P 5950 4050
AR Path="/6111FD42/60D80445" Ref="R?"  Part="1" 
AR Path="/60D6E535/60D80445" Ref="R37"  Part="1" 
F 0 "R37" V 5950 4100 50  0000 R CNN
F 1 "10k" V 5880 4095 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 5880 4050 50  0001 C CNN
F 3 "~" H 5950 4050 50  0001 C CNN
	1    5950 4050
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R?
U 1 1 60D8044B
P 5950 3750
AR Path="/6111FD42/60D8044B" Ref="R?"  Part="1" 
AR Path="/60D6E535/60D8044B" Ref="R36"  Part="1" 
F 0 "R36" V 5950 3800 50  0000 R CNN
F 1 "10k" V 6050 3800 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 5880 3750 50  0001 C CNN
F 3 "~" H 5950 3750 50  0001 C CNN
	1    5950 3750
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60D80451
P 6100 4050
AR Path="/6111FD42/60D80451" Ref="#PWR?"  Part="1" 
AR Path="/60D6E535/60D80451" Ref="#PWR0112"  Part="1" 
F 0 "#PWR0112" H 6100 3800 50  0001 C CNN
F 1 "GND" V 6100 3900 50  0000 R CNN
F 2 "" H 6100 4050 50  0001 C CNN
F 3 "" H 6100 4050 50  0001 C CNN
	1    6100 4050
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5800 3750 5800 3850
Wire Wire Line
	5800 3950 5800 4050
Wire Wire Line
	5800 3850 7050 3850
Connection ~ 5800 3850
Wire Wire Line
	5800 3950 7050 3950
Connection ~ 5800 3950
Wire Wire Line
	7050 4050 6500 4050
Wire Wire Line
	6500 4050 6500 4250
Text Notes 4800 4000 0    25   ~ 0
simply two unused lines from cat cable. \npulled to gnd if unused, otherwise for\nprototyping / testing..
Text HLabel 4650 3000 0    50   Input ~ 0
Stepper_DIR
Wire Wire Line
	4650 3000 5000 3000
Text HLabel 4650 3550 0    50   Input ~ 0
Stepper_STEP
Text HLabel 4650 4900 0    50   Output ~ 0
Stepper_END
Text HLabel 4650 4250 0    50   Output ~ 0
END_ALL
Wire Wire Line
	4650 4250 6500 4250
$EndSCHEMATC
