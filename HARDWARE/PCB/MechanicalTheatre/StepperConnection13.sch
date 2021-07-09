EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 14 15
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
U 5 1 60F21724
P 7250 4050
AR Path="/6111FD42/60F21724" Ref="J?"  Part="1" 
AR Path="/60F0C4E2/60F21724" Ref="J12"  Part="5" 
AR Path="/60F21724" Ref="J12"  Part="5" 
F 0 "J12" H 7307 4717 50  0000 C CNN
F 1 "RJ45 8x Socket" H 7307 4626 50  0000 C CNN
F 2 "Clockdiv-KiCad:RJ45_Conrad_8x" V 7250 4075 50  0001 C CNN
F 3 "~" V 7250 4075 50  0001 C CNN
	5    7250 4050
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60F2172A
P 6850 4350
AR Path="/6111FD42/60F2172A" Ref="#PWR?"  Part="1" 
AR Path="/60F0C4E2/60F2172A" Ref="#PWR0171"  Part="1" 
F 0 "#PWR0171" H 6850 4100 50  0001 C CNN
F 1 "GND" V 6850 4250 50  0000 R CNN
F 2 "" H 6850 4350 50  0001 C CNN
F 3 "" H 6850 4350 50  0001 C CNN
	1    6850 4350
	0    1    1    0   
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 60F21730
P 6850 3850
AR Path="/6111FD42/60F21730" Ref="#PWR?"  Part="1" 
AR Path="/60F0C4E2/60F21730" Ref="#PWR0170"  Part="1" 
F 0 "#PWR0170" H 6850 3700 50  0001 C CNN
F 1 "+5V" V 6865 3978 50  0000 L CNN
F 2 "" H 6850 3850 50  0001 C CNN
F 3 "" H 6850 3850 50  0001 C CNN
	1    6850 3850
	0    -1   -1   0   
$EndComp
$Comp
L Clockdiv-KiCad-library:SN74AHCT125N U?
U 2 1 60F21736
P 5100 3700
AR Path="/6111FD42/60F21736" Ref="U?"  Part="2" 
AR Path="/60F0C4E2/60F21736" Ref="U13"  Part="2" 
F 0 "U13" H 5300 3600 50  0000 C CNN
F 1 "SN74AHCT125N" H 5450 3850 50  0000 C CNN
F 2 "Package_SO:SO-14_5.3x10.2mm_P1.27mm" H 5100 3700 50  0001 C CNN
F 3 "https://www.ti.com/general/docs/suppproductinfo.tsp?distId=10&gotoUrl=https%3A%2F%2Fwww.ti.com%2Flit%2Fgpn%2Fsn74ahct125" H 5100 3700 50  0001 C CNN
	2    5100 3700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60F2173C
P 4800 3650
AR Path="/6111FD42/60F2173C" Ref="#PWR?"  Part="1" 
AR Path="/60F0C4E2/60F2173C" Ref="#PWR0162"  Part="1" 
F 0 "#PWR0162" H 4800 3400 50  0001 C CNN
F 1 "GND" V 4805 3522 50  0000 R CNN
F 2 "" H 4800 3650 50  0001 C CNN
F 3 "" H 4800 3650 50  0001 C CNN
	1    4800 3650
	0    1    1    0   
$EndComp
Wire Wire Line
	4800 3750 4450 3750
$Comp
L Clockdiv-KiCad-library:SN74HC14S U?
U 1 1 60F21743
P 5400 5100
AR Path="/6111FD42/60F21743" Ref="U?"  Part="1" 
AR Path="/60F0C4E2/60F21743" Ref="U14"  Part="1" 
F 0 "U14" H 5650 5200 50  0000 R CNN
F 1 "SN74HC14S" H 5900 5000 50  0000 R CNN
F 2 "Package_SO:SO-14_5.3x10.2mm_P1.27mm" H 5400 5100 50  0001 C CNN
F 3 "https://www.ti.com/lit/gpn/sn74hc14" H 5400 5100 50  0001 C CNN
	1    5400 5100
	-1   0    0    -1  
$EndComp
Wire Wire Line
	5100 5100 4450 5100
$Comp
L power:GND #PWR?
U 1 1 60F2174A
P 5450 5400
AR Path="/6111FD42/60F2174A" Ref="#PWR?"  Part="1" 
AR Path="/60F0C4E2/60F2174A" Ref="#PWR0166"  Part="1" 
F 0 "#PWR0166" H 5450 5150 50  0001 C CNN
F 1 "GND" H 5400 5350 50  0000 R CNN
F 2 "" H 5450 5400 50  0001 C CNN
F 3 "" H 5450 5400 50  0001 C CNN
	1    5450 5400
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 60F21750
P 5550 4700
AR Path="/6111FD42/60F21750" Ref="#PWR?"  Part="1" 
AR Path="/60F0C4E2/60F21750" Ref="#PWR0167"  Part="1" 
F 0 "#PWR0167" H 5550 4550 50  0001 C CNN
F 1 "+3.3V" V 5550 4800 50  0000 L CNN
F 2 "" H 5550 4700 50  0001 C CNN
F 3 "" H 5550 4700 50  0001 C CNN
	1    5550 4700
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 60F21756
P 6400 4950
AR Path="/6111FD42/60F21756" Ref="R?"  Part="1" 
AR Path="/60F0C4E2/60F21756" Ref="R63"  Part="1" 
F 0 "R63" H 6470 4996 50  0000 L CNN
F 1 "1k" H 6470 4905 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 6330 4950 50  0001 C CNN
F 3 "~" H 6400 4950 50  0001 C CNN
	1    6400 4950
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 60F2175C
P 6000 4950
AR Path="/6111FD42/60F2175C" Ref="R?"  Part="1" 
AR Path="/60F0C4E2/60F2175C" Ref="R62"  Part="1" 
F 0 "R62" H 5930 4904 50  0000 R CNN
F 1 "10k" H 5930 4995 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 5930 4950 50  0001 C CNN
F 3 "~" H 6000 4950 50  0001 C CNN
	1    6000 4950
	-1   0    0    1   
$EndComp
Wire Wire Line
	5700 5100 6000 5100
Connection ~ 6000 5100
Wire Wire Line
	5450 4900 5450 4800
$Comp
L Device:C C?
U 1 1 60F21765
P 6000 5250
AR Path="/6111FD42/60F21765" Ref="C?"  Part="1" 
AR Path="/60F0C4E2/60F21765" Ref="C18"  Part="1" 
F 0 "C18" H 6115 5296 50  0000 L CNN
F 1 "0.1uF 16V" H 6115 5205 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 6038 5100 50  0001 C CNN
F 3 "~" H 6000 5250 50  0001 C CNN
	1    6000 5250
	1    0    0    -1  
$EndComp
Wire Wire Line
	5450 5400 5450 5300
Wire Wire Line
	5450 5400 6000 5400
Connection ~ 5450 5400
Wire Wire Line
	6000 4800 5450 4800
Wire Wire Line
	6000 5100 6400 5100
$Comp
L power:GND #PWR?
U 1 1 60F21770
P 4950 4700
AR Path="/6111FD42/60F21770" Ref="#PWR?"  Part="1" 
AR Path="/60F0C4E2/60F21770" Ref="#PWR0163"  Part="1" 
F 0 "#PWR0163" H 4950 4450 50  0001 C CNN
F 1 "GND" V 4950 4600 50  0000 R CNN
F 2 "" H 4950 4700 50  0001 C CNN
F 3 "" H 4950 4700 50  0001 C CNN
	1    4950 4700
	0    1    1    0   
$EndComp
Wire Wire Line
	5450 4800 5450 4700
Connection ~ 5450 4800
Connection ~ 5450 4700
Wire Wire Line
	5450 4700 5550 4700
Wire Wire Line
	4950 4700 5150 4700
$Comp
L Device:C C?
U 1 1 60F2177C
P 5300 4700
AR Path="/6111FD42/60F2177C" Ref="C?"  Part="1" 
AR Path="/60F0C4E2/60F2177C" Ref="C17"  Part="1" 
F 0 "C17" V 5250 4750 50  0000 L CNN
F 1 "0.1uF 16V " V 5400 4500 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 5338 4550 50  0001 C CNN
F 3 "~" H 5300 4700 50  0001 C CNN
F 4 "place near SN74HC14s" V 5400 4100 50  0000 C CNN "Comment"
	1    5300 4700
	0    -1   -1   0   
$EndComp
$Comp
L Clockdiv-KiCad-library:SN74AHCT125N U?
U 1 1 60F21782
P 5100 3150
AR Path="/6111FD42/60F21782" Ref="U?"  Part="1" 
AR Path="/60F0C4E2/60F21782" Ref="U13"  Part="1" 
F 0 "U13" H 5200 3050 50  0000 L CNN
F 1 "SN74AHCT125N" H 5150 3300 50  0000 L CNN
F 2 "Package_SO:SO-14_5.3x10.2mm_P1.27mm" H 5100 3150 50  0001 C CNN
F 3 "https://www.ti.com/general/docs/suppproductinfo.tsp?distId=10&gotoUrl=https%3A%2F%2Fwww.ti.com%2Flit%2Fgpn%2Fsn74ahct125" H 5100 3150 50  0001 C CNN
	1    5100 3150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60F21788
P 5050 3350
AR Path="/6111FD42/60F21788" Ref="#PWR?"  Part="1" 
AR Path="/60F0C4E2/60F21788" Ref="#PWR0165"  Part="1" 
F 0 "#PWR0165" H 5050 3100 50  0001 C CNN
F 1 "GND" H 5000 3300 50  0000 R CNN
F 2 "" H 5050 3350 50  0001 C CNN
F 3 "" H 5050 3350 50  0001 C CNN
	1    5050 3350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60F2178E
P 4800 3100
AR Path="/6111FD42/60F2178E" Ref="#PWR?"  Part="1" 
AR Path="/60F0C4E2/60F2178E" Ref="#PWR0161"  Part="1" 
F 0 "#PWR0161" H 4800 2850 50  0001 C CNN
F 1 "GND" V 4805 2972 50  0000 R CNN
F 2 "" H 4800 3100 50  0001 C CNN
F 3 "" H 4800 3100 50  0001 C CNN
	1    4800 3100
	0    1    1    0   
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 60F21794
P 5050 2950
AR Path="/6111FD42/60F21794" Ref="#PWR?"  Part="1" 
AR Path="/60F0C4E2/60F21794" Ref="#PWR0164"  Part="1" 
F 0 "#PWR0164" H 5050 2800 50  0001 C CNN
F 1 "+5V" H 4850 3000 50  0000 L CNN
F 2 "" H 5050 2950 50  0001 C CNN
F 3 "" H 5050 2950 50  0001 C CNN
	1    5050 2950
	1    0    0    -1  
$EndComp
Text Label 3600 2700 0    200  ~ 0
STEPPER_MOTOR_CONNECTION_13
Text Notes 6800 3500 2    50   ~ 0
DIR
Text Notes 6450 3650 2    50   ~ 0
STEP
Text Notes 6800 4250 2    50   ~ 0
END 2
Text Notes 6800 4450 2    50   ~ 0
END 1
Wire Wire Line
	6650 3150 6650 3750
Wire Wire Line
	6650 3750 6850 3750
Wire Wire Line
	6400 4450 6850 4450
$Comp
L Connector:Conn_01x02_Male J?
U 1 1 60F217A2
P 5400 4050
AR Path="/6111FD42/60F217A2" Ref="J?"  Part="1" 
AR Path="/60F0C4E2/60F217A2" Ref="J21"  Part="1" 
F 0 "J21" H 5450 4100 25  0000 C CNN
F 1 "Conn_01x02_General Purpose 13" H 5000 4100 25  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 5400 4050 50  0001 C CNN
F 3 "~" H 5400 4050 50  0001 C CNN
	1    5400 4050
	1    0    0    -1  
$EndComp
Wire Wire Line
	5400 3150 6650 3150
Wire Wire Line
	5400 3700 6500 3700
Wire Wire Line
	6500 3700 6500 3950
Wire Wire Line
	6500 3950 6850 3950
Wire Wire Line
	6400 4450 6400 4800
$Comp
L power:GND #PWR?
U 1 1 60F217AD
P 5900 3950
AR Path="/6111FD42/60F217AD" Ref="#PWR?"  Part="1" 
AR Path="/60F0C4E2/60F217AD" Ref="#PWR0168"  Part="1" 
F 0 "#PWR0168" H 5900 3700 50  0001 C CNN
F 1 "GND" V 5900 3800 50  0000 R CNN
F 2 "" H 5900 3950 50  0001 C CNN
F 3 "" H 5900 3950 50  0001 C CNN
	1    5900 3950
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R?
U 1 1 60F217B3
P 5750 4250
AR Path="/6111FD42/60F217B3" Ref="R?"  Part="1" 
AR Path="/60F0C4E2/60F217B3" Ref="R61"  Part="1" 
F 0 "R61" V 5750 4300 50  0000 R CNN
F 1 "10k" V 5680 4295 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 5680 4250 50  0001 C CNN
F 3 "~" H 5750 4250 50  0001 C CNN
	1    5750 4250
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R?
U 1 1 60F217B9
P 5750 3950
AR Path="/6111FD42/60F217B9" Ref="R?"  Part="1" 
AR Path="/60F0C4E2/60F217B9" Ref="R60"  Part="1" 
F 0 "R60" V 5750 4000 50  0000 R CNN
F 1 "10k" V 5850 4000 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 5680 3950 50  0001 C CNN
F 3 "~" H 5750 3950 50  0001 C CNN
	1    5750 3950
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60F217BF
P 5900 4250
AR Path="/6111FD42/60F217BF" Ref="#PWR?"  Part="1" 
AR Path="/60F0C4E2/60F217BF" Ref="#PWR0169"  Part="1" 
F 0 "#PWR0169" H 5900 4000 50  0001 C CNN
F 1 "GND" V 5900 4100 50  0000 R CNN
F 2 "" H 5900 4250 50  0001 C CNN
F 3 "" H 5900 4250 50  0001 C CNN
	1    5900 4250
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5600 3950 5600 4050
Wire Wire Line
	5600 4150 5600 4250
Wire Wire Line
	5600 4050 6850 4050
Connection ~ 5600 4050
Wire Wire Line
	5600 4150 6850 4150
Connection ~ 5600 4150
Wire Wire Line
	6850 4250 6300 4250
Wire Wire Line
	6300 4250 6300 4450
Text Notes 4600 4200 0    25   ~ 0
simply two unused lines from cat cable. \npulled to gnd if unused, otherwise for\nprototyping / testing..
Text HLabel 4450 3200 0    50   Input ~ 0
Stepper_DIR
Wire Wire Line
	4450 3200 4800 3200
Text HLabel 4450 3750 0    50   Input ~ 0
Stepper_STEP
Text HLabel 4450 5100 0    50   Output ~ 0
Stepper_END
Text HLabel 4450 4450 0    50   Output ~ 0
END_ALL
Wire Wire Line
	4450 4450 6300 4450
$EndSCHEMATC
