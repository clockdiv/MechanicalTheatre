EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 10 15
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
U 1 1 60D91C5C
P 7250 4100
AR Path="/6111FD42/60D91C5C" Ref="J?"  Part="1" 
AR Path="/60D6EEA1/60D91C5C" Ref="J12"  Part="1" 
AR Path="/60D91C5C" Ref="J12"  Part="1" 
F 0 "J12" H 7307 4767 50  0000 C CNN
F 1 "RJ45 8x Socket" H 7307 4676 50  0000 C CNN
F 2 "Clockdiv-KiCad:RJ45_Conrad_8x" V 7250 4125 50  0001 C CNN
F 3 "~" V 7250 4125 50  0001 C CNN
	1    7250 4100
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60D91C62
P 6850 4400
AR Path="/6111FD42/60D91C62" Ref="#PWR?"  Part="1" 
AR Path="/60D6EEA1/60D91C62" Ref="#PWR0132"  Part="1" 
F 0 "#PWR0132" H 6850 4150 50  0001 C CNN
F 1 "GND" V 6850 4300 50  0000 R CNN
F 2 "" H 6850 4400 50  0001 C CNN
F 3 "" H 6850 4400 50  0001 C CNN
	1    6850 4400
	0    1    1    0   
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 60D91C68
P 6850 3900
AR Path="/6111FD42/60D91C68" Ref="#PWR?"  Part="1" 
AR Path="/60D6EEA1/60D91C68" Ref="#PWR0131"  Part="1" 
F 0 "#PWR0131" H 6850 3750 50  0001 C CNN
F 1 "+5V" V 6865 4028 50  0000 L CNN
F 2 "" H 6850 3900 50  0001 C CNN
F 3 "" H 6850 3900 50  0001 C CNN
	1    6850 3900
	0    -1   -1   0   
$EndComp
$Comp
L Clockdiv-KiCad-library:SN74AHCT125N U?
U 2 1 60D91C6E
P 5100 3750
AR Path="/6111FD42/60D91C6E" Ref="U?"  Part="2" 
AR Path="/60D6EEA1/60D91C6E" Ref="U11"  Part="2" 
F 0 "U11" H 5300 3650 50  0000 C CNN
F 1 "SN74AHCT125N" H 5450 3900 50  0000 C CNN
F 2 "Package_SO:SO-14_5.3x10.2mm_P1.27mm" H 5100 3750 50  0001 C CNN
F 3 "https://www.ti.com/general/docs/suppproductinfo.tsp?distId=10&gotoUrl=https%3A%2F%2Fwww.ti.com%2Flit%2Fgpn%2Fsn74ahct125" H 5100 3750 50  0001 C CNN
	2    5100 3750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60D91C74
P 4800 3700
AR Path="/6111FD42/60D91C74" Ref="#PWR?"  Part="1" 
AR Path="/60D6EEA1/60D91C74" Ref="#PWR0124"  Part="1" 
F 0 "#PWR0124" H 4800 3450 50  0001 C CNN
F 1 "GND" V 4805 3572 50  0000 R CNN
F 2 "" H 4800 3700 50  0001 C CNN
F 3 "" H 4800 3700 50  0001 C CNN
	1    4800 3700
	0    1    1    0   
$EndComp
Wire Wire Line
	4800 3800 4450 3800
$Comp
L Clockdiv-KiCad-library:SN74HC14S U?
U 3 1 60D91C7B
P 5400 5150
AR Path="/6111FD42/60D91C7B" Ref="U?"  Part="1" 
AR Path="/60D6EEA1/60D91C7B" Ref="U10"  Part="3" 
F 0 "U10" H 5650 5250 50  0000 R CNN
F 1 "SN74HC14S" H 5900 5050 50  0000 R CNN
F 2 "Package_SO:SO-14_5.3x10.2mm_P1.27mm" H 5400 5150 50  0001 C CNN
F 3 "https://www.ti.com/lit/gpn/sn74hc14" H 5400 5150 50  0001 C CNN
	3    5400 5150
	-1   0    0    -1  
$EndComp
Wire Wire Line
	5100 5150 4450 5150
$Comp
L power:GND #PWR?
U 1 1 60D91C82
P 5450 5450
AR Path="/6111FD42/60D91C82" Ref="#PWR?"  Part="1" 
AR Path="/60D6EEA1/60D91C82" Ref="#PWR0127"  Part="1" 
F 0 "#PWR0127" H 5450 5200 50  0001 C CNN
F 1 "GND" H 5400 5400 50  0000 R CNN
F 2 "" H 5450 5450 50  0001 C CNN
F 3 "" H 5450 5450 50  0001 C CNN
	1    5450 5450
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 60D91C88
P 5550 4750
AR Path="/6111FD42/60D91C88" Ref="#PWR?"  Part="1" 
AR Path="/60D6EEA1/60D91C88" Ref="#PWR0128"  Part="1" 
F 0 "#PWR0128" H 5550 4600 50  0001 C CNN
F 1 "+3.3V" V 5550 4850 50  0000 L CNN
F 2 "" H 5550 4750 50  0001 C CNN
F 3 "" H 5550 4750 50  0001 C CNN
	1    5550 4750
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 60D91C8E
P 6400 5000
AR Path="/6111FD42/60D91C8E" Ref="R?"  Part="1" 
AR Path="/60D6EEA1/60D91C8E" Ref="R47"  Part="1" 
F 0 "R47" H 6470 5046 50  0000 L CNN
F 1 "1k" H 6470 4955 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 6330 5000 50  0001 C CNN
F 3 "~" H 6400 5000 50  0001 C CNN
	1    6400 5000
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 60D91C94
P 6000 5000
AR Path="/6111FD42/60D91C94" Ref="R?"  Part="1" 
AR Path="/60D6EEA1/60D91C94" Ref="R46"  Part="1" 
F 0 "R46" H 5930 4954 50  0000 R CNN
F 1 "10k" H 5930 5045 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 5930 5000 50  0001 C CNN
F 3 "~" H 6000 5000 50  0001 C CNN
	1    6000 5000
	-1   0    0    1   
$EndComp
Wire Wire Line
	5700 5150 6000 5150
Connection ~ 6000 5150
$Comp
L Device:C C?
U 1 1 60D91C9D
P 6000 5300
AR Path="/6111FD42/60D91C9D" Ref="C?"  Part="1" 
AR Path="/60D6EEA1/60D91C9D" Ref="C13"  Part="1" 
F 0 "C13" H 6115 5346 50  0000 L CNN
F 1 "0.1uF 16V" H 6115 5255 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 6038 5150 50  0001 C CNN
F 3 "~" H 6000 5300 50  0001 C CNN
	1    6000 5300
	1    0    0    -1  
$EndComp
Wire Wire Line
	5450 5450 6000 5450
Wire Wire Line
	6000 4850 5450 4850
Wire Wire Line
	6000 5150 6400 5150
Wire Wire Line
	5450 4850 5450 4750
Wire Wire Line
	5450 4750 5550 4750
$Comp
L Clockdiv-KiCad-library:SN74AHCT125N U?
U 1 1 60D91CBA
P 5100 3200
AR Path="/6111FD42/60D91CBA" Ref="U?"  Part="1" 
AR Path="/60D6EEA1/60D91CBA" Ref="U11"  Part="1" 
F 0 "U11" H 5200 3100 50  0000 L CNN
F 1 "SN74AHCT125N" H 5150 3350 50  0000 L CNN
F 2 "Package_SO:SO-14_5.3x10.2mm_P1.27mm" H 5100 3200 50  0001 C CNN
F 3 "https://www.ti.com/general/docs/suppproductinfo.tsp?distId=10&gotoUrl=https%3A%2F%2Fwww.ti.com%2Flit%2Fgpn%2Fsn74ahct125" H 5100 3200 50  0001 C CNN
	1    5100 3200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60D91CC0
P 5050 3400
AR Path="/6111FD42/60D91CC0" Ref="#PWR?"  Part="1" 
AR Path="/60D6EEA1/60D91CC0" Ref="#PWR0126"  Part="1" 
F 0 "#PWR0126" H 5050 3150 50  0001 C CNN
F 1 "GND" H 5000 3350 50  0000 R CNN
F 2 "" H 5050 3400 50  0001 C CNN
F 3 "" H 5050 3400 50  0001 C CNN
	1    5050 3400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60D91CC6
P 4800 3150
AR Path="/6111FD42/60D91CC6" Ref="#PWR?"  Part="1" 
AR Path="/60D6EEA1/60D91CC6" Ref="#PWR0123"  Part="1" 
F 0 "#PWR0123" H 4800 2900 50  0001 C CNN
F 1 "GND" V 4805 3022 50  0000 R CNN
F 2 "" H 4800 3150 50  0001 C CNN
F 3 "" H 4800 3150 50  0001 C CNN
	1    4800 3150
	0    1    1    0   
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 60D91CCC
P 5050 3000
AR Path="/6111FD42/60D91CCC" Ref="#PWR?"  Part="1" 
AR Path="/60D6EEA1/60D91CCC" Ref="#PWR0125"  Part="1" 
F 0 "#PWR0125" H 5050 2850 50  0001 C CNN
F 1 "+5V" H 4850 3050 50  0000 L CNN
F 2 "" H 5050 3000 50  0001 C CNN
F 3 "" H 5050 3000 50  0001 C CNN
	1    5050 3000
	1    0    0    -1  
$EndComp
Text Label 3600 2750 0    200  ~ 0
STEPPER_MOTOR_CONNECTION_9
Text Notes 6800 3550 2    50   ~ 0
DIR
Text Notes 6450 3700 2    50   ~ 0
STEP
Text Notes 6800 4300 2    50   ~ 0
END 2
Text Notes 6800 4500 2    50   ~ 0
END 1
Wire Wire Line
	6650 3200 6650 3800
Wire Wire Line
	6650 3800 6850 3800
Wire Wire Line
	6400 4500 6850 4500
$Comp
L Connector:Conn_01x02_Male J?
U 1 1 60D91CDA
P 5400 4100
AR Path="/6111FD42/60D91CDA" Ref="J?"  Part="1" 
AR Path="/60D6EEA1/60D91CDA" Ref="J17"  Part="1" 
F 0 "J17" H 5450 4150 25  0000 C CNN
F 1 "Conn_01x02_General Purpose 09" H 5000 4150 25  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 5400 4100 50  0001 C CNN
F 3 "~" H 5400 4100 50  0001 C CNN
	1    5400 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	5400 3200 6650 3200
Wire Wire Line
	5400 3750 6500 3750
Wire Wire Line
	6500 3750 6500 4000
Wire Wire Line
	6500 4000 6850 4000
Wire Wire Line
	6400 4500 6400 4850
$Comp
L power:GND #PWR?
U 1 1 60D91CE5
P 5900 4000
AR Path="/6111FD42/60D91CE5" Ref="#PWR?"  Part="1" 
AR Path="/60D6EEA1/60D91CE5" Ref="#PWR0129"  Part="1" 
F 0 "#PWR0129" H 5900 3750 50  0001 C CNN
F 1 "GND" V 5900 3850 50  0000 R CNN
F 2 "" H 5900 4000 50  0001 C CNN
F 3 "" H 5900 4000 50  0001 C CNN
	1    5900 4000
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R?
U 1 1 60D91CEB
P 5750 4300
AR Path="/6111FD42/60D91CEB" Ref="R?"  Part="1" 
AR Path="/60D6EEA1/60D91CEB" Ref="R45"  Part="1" 
F 0 "R45" V 5750 4350 50  0000 R CNN
F 1 "10k" V 5680 4345 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 5680 4300 50  0001 C CNN
F 3 "~" H 5750 4300 50  0001 C CNN
	1    5750 4300
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R?
U 1 1 60D91CF1
P 5750 4000
AR Path="/6111FD42/60D91CF1" Ref="R?"  Part="1" 
AR Path="/60D6EEA1/60D91CF1" Ref="R44"  Part="1" 
F 0 "R44" V 5750 4050 50  0000 R CNN
F 1 "10k" V 5850 4050 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 5680 4000 50  0001 C CNN
F 3 "~" H 5750 4000 50  0001 C CNN
	1    5750 4000
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60D91CF7
P 5900 4300
AR Path="/6111FD42/60D91CF7" Ref="#PWR?"  Part="1" 
AR Path="/60D6EEA1/60D91CF7" Ref="#PWR0130"  Part="1" 
F 0 "#PWR0130" H 5900 4050 50  0001 C CNN
F 1 "GND" V 5900 4150 50  0000 R CNN
F 2 "" H 5900 4300 50  0001 C CNN
F 3 "" H 5900 4300 50  0001 C CNN
	1    5900 4300
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5600 4000 5600 4100
Wire Wire Line
	5600 4200 5600 4300
Wire Wire Line
	5600 4100 6850 4100
Connection ~ 5600 4100
Wire Wire Line
	5600 4200 6850 4200
Connection ~ 5600 4200
Wire Wire Line
	6850 4300 6300 4300
Wire Wire Line
	6300 4300 6300 4500
Text Notes 4600 4250 0    25   ~ 0
simply two unused lines from cat cable. \npulled to gnd if unused, otherwise for\nprototyping / testing..
Text HLabel 4450 3250 0    50   Input ~ 0
Stepper_DIR
Wire Wire Line
	4450 3250 4800 3250
Text HLabel 4450 3800 0    50   Input ~ 0
Stepper_STEP
Text HLabel 4450 5150 0    50   Output ~ 0
Stepper_END
Text HLabel 4450 4500 0    50   Output ~ 0
END_ALL
Wire Wire Line
	4450 4500 6300 4500
$Comp
L power:GND #PWR?
U 1 1 60D7A678
P 7250 3600
AR Path="/6111FD42/60D7A678" Ref="#PWR?"  Part="1" 
AR Path="/60D6EEA1/60D7A678" Ref="#PWR0154"  Part="1" 
F 0 "#PWR0154" H 7250 3350 50  0001 C CNN
F 1 "GND" V 7250 3450 50  0000 R CNN
F 2 "" H 7250 3600 50  0001 C CNN
F 3 "" H 7250 3600 50  0001 C CNN
	1    7250 3600
	-1   0    0    1   
$EndComp
$EndSCHEMATC
