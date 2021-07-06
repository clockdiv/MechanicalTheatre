EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 5 15
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
U 4 1 60D2E964
P 7150 3950
AR Path="/6111FD42/60D2E964" Ref="J?"  Part="1" 
AR Path="/611E4390/60D2E964" Ref="J11"  Part="4" 
F 0 "J11" H 7207 4617 50  0000 C CNN
F 1 "RJ45 8x Socket" H 7207 4526 50  0000 C CNN
F 2 "Clockdiv-KiCad:RJ45_Conrad_8x" V 7150 3975 50  0001 C CNN
F 3 "~" V 7150 3975 50  0001 C CNN
	4    7150 3950
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60D2E96A
P 6750 4250
AR Path="/6111FD42/60D2E96A" Ref="#PWR?"  Part="1" 
AR Path="/611E4390/60D2E96A" Ref="#PWR085"  Part="1" 
F 0 "#PWR085" H 6750 4000 50  0001 C CNN
F 1 "GND" V 6750 4150 50  0000 R CNN
F 2 "" H 6750 4250 50  0001 C CNN
F 3 "" H 6750 4250 50  0001 C CNN
	1    6750 4250
	0    1    1    0   
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 60D2E970
P 6750 3750
AR Path="/6111FD42/60D2E970" Ref="#PWR?"  Part="1" 
AR Path="/611E4390/60D2E970" Ref="#PWR084"  Part="1" 
F 0 "#PWR084" H 6750 3600 50  0001 C CNN
F 1 "+5V" V 6765 3878 50  0000 L CNN
F 2 "" H 6750 3750 50  0001 C CNN
F 3 "" H 6750 3750 50  0001 C CNN
	1    6750 3750
	0    -1   -1   0   
$EndComp
$Comp
L Clockdiv-KiCad-library:SN74AHCT125N U?
U 4 1 60D2E976
P 5000 3600
AR Path="/6111FD42/60D2E976" Ref="U?"  Part="2" 
AR Path="/611E4390/60D2E976" Ref="U7"  Part="4" 
F 0 "U7" H 5200 3500 50  0000 C CNN
F 1 "SN74AHCT125N" H 5350 3750 50  0000 C CNN
F 2 "Package_SO:SO-14_5.3x10.2mm_P1.27mm" H 5000 3600 50  0001 C CNN
F 3 "https://www.ti.com/general/docs/suppproductinfo.tsp?distId=10&gotoUrl=https%3A%2F%2Fwww.ti.com%2Flit%2Fgpn%2Fsn74ahct125" H 5000 3600 50  0001 C CNN
	4    5000 3600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60D2E97C
P 4700 3550
AR Path="/6111FD42/60D2E97C" Ref="#PWR?"  Part="1" 
AR Path="/611E4390/60D2E97C" Ref="#PWR079"  Part="1" 
F 0 "#PWR079" H 4700 3300 50  0001 C CNN
F 1 "GND" V 4705 3422 50  0000 R CNN
F 2 "" H 4700 3550 50  0001 C CNN
F 3 "" H 4700 3550 50  0001 C CNN
	1    4700 3550
	0    1    1    0   
$EndComp
Wire Wire Line
	4700 3650 4350 3650
$Comp
L Clockdiv-KiCad-library:SN74HC14S U?
U 4 1 60D2E983
P 5300 5000
AR Path="/6111FD42/60D2E983" Ref="U?"  Part="1" 
AR Path="/611E4390/60D2E983" Ref="U6"  Part="4" 
F 0 "U6" H 5550 5100 50  0000 R CNN
F 1 "SN74HC14S" H 5800 4900 50  0000 R CNN
F 2 "Package_SO:SO-14_5.3x10.2mm_P1.27mm" H 5300 5000 50  0001 C CNN
F 3 "https://www.ti.com/lit/gpn/sn74hc14" H 5300 5000 50  0001 C CNN
	4    5300 5000
	-1   0    0    -1  
$EndComp
Wire Wire Line
	5000 5000 4350 5000
$Comp
L power:GND #PWR?
U 1 1 60D2E98A
P 5350 5300
AR Path="/6111FD42/60D2E98A" Ref="#PWR?"  Part="1" 
AR Path="/611E4390/60D2E98A" Ref="#PWR080"  Part="1" 
F 0 "#PWR080" H 5350 5050 50  0001 C CNN
F 1 "GND" H 5300 5250 50  0000 R CNN
F 2 "" H 5350 5300 50  0001 C CNN
F 3 "" H 5350 5300 50  0001 C CNN
	1    5350 5300
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 60D2E990
P 5450 4600
AR Path="/6111FD42/60D2E990" Ref="#PWR?"  Part="1" 
AR Path="/611E4390/60D2E990" Ref="#PWR081"  Part="1" 
F 0 "#PWR081" H 5450 4450 50  0001 C CNN
F 1 "+3.3V" V 5450 4700 50  0000 L CNN
F 2 "" H 5450 4600 50  0001 C CNN
F 3 "" H 5450 4600 50  0001 C CNN
	1    5450 4600
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 60D2E996
P 6300 4850
AR Path="/6111FD42/60D2E996" Ref="R?"  Part="1" 
AR Path="/611E4390/60D2E996" Ref="R27"  Part="1" 
F 0 "R27" H 6370 4896 50  0000 L CNN
F 1 "1k" H 6370 4805 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 6230 4850 50  0001 C CNN
F 3 "~" H 6300 4850 50  0001 C CNN
	1    6300 4850
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 60D2E99C
P 5900 4850
AR Path="/6111FD42/60D2E99C" Ref="R?"  Part="1" 
AR Path="/611E4390/60D2E99C" Ref="R26"  Part="1" 
F 0 "R26" H 5830 4804 50  0000 R CNN
F 1 "10k" H 5830 4895 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 5830 4850 50  0001 C CNN
F 3 "~" H 5900 4850 50  0001 C CNN
	1    5900 4850
	-1   0    0    1   
$EndComp
Wire Wire Line
	5600 5000 5900 5000
Connection ~ 5900 5000
$Comp
L Device:C C?
U 1 1 60D2E9A5
P 5900 5150
AR Path="/6111FD42/60D2E9A5" Ref="C?"  Part="1" 
AR Path="/611E4390/60D2E9A5" Ref="C7"  Part="1" 
F 0 "C7" H 6015 5196 50  0000 L CNN
F 1 "0.1uF 16V" H 6015 5105 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 5938 5000 50  0001 C CNN
F 3 "~" H 5900 5150 50  0001 C CNN
	1    5900 5150
	1    0    0    -1  
$EndComp
Wire Wire Line
	5350 5300 5900 5300
Wire Wire Line
	5900 4700 5350 4700
Wire Wire Line
	5900 5000 6300 5000
Wire Wire Line
	5350 4700 5350 4600
Wire Wire Line
	5350 4600 5450 4600
$Comp
L Clockdiv-KiCad-library:SN74AHCT125N U?
U 3 1 60D2E9C2
P 5000 3050
AR Path="/6111FD42/60D2E9C2" Ref="U?"  Part="1" 
AR Path="/611E4390/60D2E9C2" Ref="U7"  Part="3" 
F 0 "U7" H 5100 2950 50  0000 L CNN
F 1 "SN74AHCT125N" H 5050 3200 50  0000 L CNN
F 2 "Package_SO:SO-14_5.3x10.2mm_P1.27mm" H 5000 3050 50  0001 C CNN
F 3 "https://www.ti.com/general/docs/suppproductinfo.tsp?distId=10&gotoUrl=https%3A%2F%2Fwww.ti.com%2Flit%2Fgpn%2Fsn74ahct125" H 5000 3050 50  0001 C CNN
	3    5000 3050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60D2E9CE
P 4700 3000
AR Path="/6111FD42/60D2E9CE" Ref="#PWR?"  Part="1" 
AR Path="/611E4390/60D2E9CE" Ref="#PWR078"  Part="1" 
F 0 "#PWR078" H 4700 2750 50  0001 C CNN
F 1 "GND" V 4705 2872 50  0000 R CNN
F 2 "" H 4700 3000 50  0001 C CNN
F 3 "" H 4700 3000 50  0001 C CNN
	1    4700 3000
	0    1    1    0   
$EndComp
Text Label 3500 2600 0    200  ~ 0
STEPPER_MOTOR_CONNECTION_4
Text Notes 6700 3400 2    50   ~ 0
DIR
Text Notes 6350 3550 2    50   ~ 0
STEP
Text Notes 6700 4150 2    50   ~ 0
END 2
Text Notes 6700 4350 2    50   ~ 0
END 1
Wire Wire Line
	6550 3050 6550 3650
Wire Wire Line
	6550 3650 6750 3650
Wire Wire Line
	6300 4350 6750 4350
$Comp
L Connector:Conn_01x02_Male J?
U 1 1 60D2E9E2
P 5300 3950
AR Path="/6111FD42/60D2E9E2" Ref="J?"  Part="1" 
AR Path="/611E4390/60D2E9E2" Ref="J3"  Part="1" 
F 0 "J3" H 5350 4000 25  0000 C CNN
F 1 "Conn_01x02_General Purpose 04" H 4900 4000 25  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 5300 3950 50  0001 C CNN
F 3 "~" H 5300 3950 50  0001 C CNN
	1    5300 3950
	1    0    0    -1  
$EndComp
Wire Wire Line
	5300 3050 6550 3050
Wire Wire Line
	5300 3600 6400 3600
Wire Wire Line
	6400 3600 6400 3850
Wire Wire Line
	6400 3850 6750 3850
Wire Wire Line
	6300 4350 6300 4700
$Comp
L power:GND #PWR?
U 1 1 60D2E9ED
P 5800 3850
AR Path="/6111FD42/60D2E9ED" Ref="#PWR?"  Part="1" 
AR Path="/611E4390/60D2E9ED" Ref="#PWR082"  Part="1" 
F 0 "#PWR082" H 5800 3600 50  0001 C CNN
F 1 "GND" V 5800 3700 50  0000 R CNN
F 2 "" H 5800 3850 50  0001 C CNN
F 3 "" H 5800 3850 50  0001 C CNN
	1    5800 3850
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R?
U 1 1 60D2E9F3
P 5650 4150
AR Path="/6111FD42/60D2E9F3" Ref="R?"  Part="1" 
AR Path="/611E4390/60D2E9F3" Ref="R25"  Part="1" 
F 0 "R25" V 5650 4200 50  0000 R CNN
F 1 "10k" V 5580 4195 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 5580 4150 50  0001 C CNN
F 3 "~" H 5650 4150 50  0001 C CNN
	1    5650 4150
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R?
U 1 1 60D2E9F9
P 5650 3850
AR Path="/6111FD42/60D2E9F9" Ref="R?"  Part="1" 
AR Path="/611E4390/60D2E9F9" Ref="R24"  Part="1" 
F 0 "R24" V 5650 3900 50  0000 R CNN
F 1 "10k" V 5750 3900 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 5580 3850 50  0001 C CNN
F 3 "~" H 5650 3850 50  0001 C CNN
	1    5650 3850
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60D2E9FF
P 5800 4150
AR Path="/6111FD42/60D2E9FF" Ref="#PWR?"  Part="1" 
AR Path="/611E4390/60D2E9FF" Ref="#PWR083"  Part="1" 
F 0 "#PWR083" H 5800 3900 50  0001 C CNN
F 1 "GND" V 5800 4000 50  0000 R CNN
F 2 "" H 5800 4150 50  0001 C CNN
F 3 "" H 5800 4150 50  0001 C CNN
	1    5800 4150
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5500 3850 5500 3950
Wire Wire Line
	5500 4050 5500 4150
Wire Wire Line
	5500 3950 6750 3950
Connection ~ 5500 3950
Wire Wire Line
	5500 4050 6750 4050
Connection ~ 5500 4050
Wire Wire Line
	6750 4150 6200 4150
Wire Wire Line
	6200 4150 6200 4350
Text Notes 4500 4100 0    25   ~ 0
simply two unused lines from cat cable. \npulled to gnd if unused, otherwise for\nprototyping / testing..
Text HLabel 4350 3100 0    50   Input ~ 0
Stepper_DIR
Wire Wire Line
	4350 3100 4700 3100
Text HLabel 4350 3650 0    50   Input ~ 0
Stepper_STEP
Text HLabel 4350 5000 0    50   Output ~ 0
Stepper_END
Text HLabel 4350 4350 0    50   Output ~ 0
END_ALL
Wire Wire Line
	4350 4350 6200 4350
$EndSCHEMATC