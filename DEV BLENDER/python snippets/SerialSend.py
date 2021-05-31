import serial
from time import sleep 

#python3 -m serial.tools.list_ports

arduino = serial.Serial(port='/dev/cu.usbmodem11301', baudrate=9600, timeout=.1)

arduino.write(bytes('a', 'utf-8'))
