#!/usr/bin/python

# Description:
# SERIAL PORT EMULATOR
# for specific sentence to emulate MSP430

# Author         Version          Date            Change
# F.Quinto       1.0              2012-08-05      Initial release

import serial
import sys
import time
from time import time,sleep
import random

# =================== VARS ===================

# Puerto comunicaciones
port = "/dev/pts/3"
velocidad = 9600

# emulacion de AP=1 o ED=0
emulaAP = 1

# ================= END VARS =================

ser = serial.Serial(port, velocidad, timeout=0)

# estado leds inicial = OFF
estado_led1 = "001"
estado_led2 = "001"
estado_led3 = "001"
estado = "000"
data = ''
veces = 2
n = 0
while True:
	#data = ser.read(99)
	newdata = ser.readline()
	if (len(newdata) > 0):
		n = 1
		data +=  newdata
		if (len(data) == 8):
			header = data[0:1]
			readwrite = data[1:2]
			address = data[2:4]
			datamsg = data[4:7]
			print "-------------------------------------"
			print 'RECIBIDO: '+ header + readwrite + address + datamsg + ' = ',
			if (header == "A"):
				print "AP ",
				respuesta = "D"
			if (header == "B"):
				print "ED ",
				respuesta = "G"
			if (header == "C"):
				print "FPGA ",
				respuesta = "J"
			if (readwrite == "R"):
				print "READ ",
			if (readwrite == "W"):
				print "WRITE ",
			if (address == "10"):
				print "Led2 (rojo) ",
				if (readwrite == "W"):
					if (datamsg == "000"):
						#ON
						estado_led2 = "000"
					else:
						#OFF
						estado_led2 = "001"
				estado = estado_led2
			if (address == "11"):
				print "Led1 (verde) ",
				if (readwrite == "W"):
					if (datamsg == "000"):
						#ON
						estado_led1 = "000"
					else:
						#OFF
						estado_led1 = "001"
				estado = estado_led1
			if (address == "12"):
				print "Button ",
				if (datamsg == "000"):
					estado = "000"
			if (address == "20"):
				print "Led3 (amarillo) ",
				if (readwrite == "W"):
					if (datamsg == "000"):
						#ON
						estado_led3 = "000"
					else:
						#OFF
						estado_led3 = "001"
				estado = estado_led3
			if (address == "50"):
				print "Temperatura ",
				if (readwrite == "R"):
					if (datamsg == "000"):
						a = "2"
						b = str(random.randint(7, 9))
						c = str(random.randint(0, 9))
						estado = a + b + c
			if (address == "51"):
				print "RSSI ",
				if (readwrite == "R"):
					if (datamsg == "000"):
						a = str(random.randint(2, 3))
						b = str(random.randint(0, 9))
						c = str(random.randint(0, 9))
						estado = a + b + c
			if (address == "52"):
				print "Voltage ",
				if (readwrite == "R"):
					if (datamsg == "000"):
						a = "3"
						b = str(random.randint(5, 6))
						c = str(random.randint(0, 9))
						estado = a + b + c
			if (address == "60"):
				print "Set address ED ",
				print datamsg
			if (address == "61"):
				print "Set address AP ",
				print datamsg
			if (address == "62"):
				if (datamsg == "000"):
					print "Setup ED "
				if (datamsg == "001"):
					print "Setup AP "
				datamsg = "xxx"
			if (datamsg == "000"):
				print "ON"
			if (datamsg == "001"):
				print "OFF"
			if (readwrite == "R"):
				envia = respuesta + "R" + address + estado + "\r\n"
				print 'ENVIA:',envia
				ser.write(envia)
			#if (data == (header+readwrite+address+"123\r")):
				#envia = "DNode:AP,Temp: 34.5C,Battery:3.7V,Strength:028%\r\n"
				#print 'ENVIA:',envia
				#ser.write(envia)
			data = ''
			veces = 2
		if (veces < 1):
			data = ''
			veces = 2
		veces = veces - 1
ser.close()
