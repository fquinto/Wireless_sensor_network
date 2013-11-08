#!C:\Python32\python.exe -u
#!/usr/bin/env python
# Import modules for CGI handling

# CALL:  http://127.0.0.1/serie/cgi-bin/recibir_windows_json.py?puerto=COM3&velocidad=9600&databit=8&stopbit=1&paridad=none&control=none

import cgi, cgitb
import serial
import sys
import time
from time import time,sleep
import re
import json

#VARIABLES que podemos coger de la web: veces de repeticion y timeout del puerto serie

# Create instance of FieldStorage
form = cgi.FieldStorage() # instantiate only once!
puerto = form.getvalue('puerto')
velocidad = form.getvalue('velocidad')
databit = form.getvalue('databit')
if (databit == "5"):
	databit = serial.FIVEBITS
if (databit == "6"):
	databit = serial.SIXBITS
if (databit == "7"):
	databit = serial.SEVENBITS
if (databit == "8"):
	databit = serial.EIGHTBITS
stopbit = form.getvalue('stopbit')
if (stopbit == "1"):
	stopbit = serial.STOPBITS_ONE
if (stopbit == "1.5"):
	stopbit = serial.STOPBITS_ONE_POINT_FIVE
if (stopbit == "2.0"):
	stopbit = serial.STOPBITS_TWO
paridad = form.getvalue('paridad')
if (paridad == "none"):
	paridad = serial.PARITY_NONE
if (paridad == "odd"):
	paridad = serial.PARITY_ODD
if (paridad == "even"):
	paridad = serial.PARITY_EVEN
control = form.getvalue('control')
if (control == "none"):
	hard=0
	soft=0
if (control == "rts/cts"):
	hard=1
	soft=0
if (control == "xon/xoff"):
	hard=0
	soft=1
veces = 2
x = time()*1000
print ("Content-Type: application/json\n")
try:
	ser = serial.Serial()
	ser.port = puerto
	ser.baudrate = velocidad
	ser.timeout = 2
	ser.parity = paridad
	ser.stopbits = stopbit
	ser.bytesize = databit
	ser.rtscts = hard
	ser.xonxoff = soft
	ser.open()
except:
	temp = 0
	jsondata = [round(x, 0), temp]
	print (json.dumps( jsondata ))
else:
	#ser.write(b'A')
	#sleep(0.01)
	#ser.write(b'info\r')
	header = form.getvalue('header')
	while True:
		# temp
		envia_msg = header+"R50000\r"
		ser.write(envia_msg.encode())
		sleep(0.15)
		data = ser.readline()
		if (len(data) > 0):
			datamsg = data[4:7].decode('utf-8')
			temp = float(datamsg[0]+datamsg[1]+'.'+datamsg[2])
		# battery
		envia_msg = header+"R52000\r"
		ser.write(envia_msg.encode())
		sleep(0.15)
		data = ser.readline()
		if (len(data) > 0):
			datamsg = data[4:7].decode('utf-8')
			bat = float(datamsg[0]+'.'+datamsg[1]+datamsg[2])
		# rssi
		envia_msg = header+"R51000\r"
		ser.write(envia_msg.encode())
		sleep(0.15)
		data = ser.readline()
		if (len(data) > 0):
			datamsg = data[4:7].decode('utf-8')
			rssi = float(datamsg[0]+datamsg[1]+'.'+datamsg[2])
		#print (data)
		#pat = r'DNode:(.*),Temp:(.*)C,Battery:(.*)V,Strength:(.*)%'
		#r = re.compile(pat)
		#m = r.match(data.decode())
		#if m:
		  #temp = float(m.group(2).lstrip())
		  #bat = float(m.group(3))
		  #rssi = float(m.group(4))
		#else:
		  #temp = 0
		  #bat = 0
		  #rssi = 0
		sys.stdout.flush()
		if (veces == 1):
				break
		veces = veces - 1
	ser.close()
	jsondata = [[round(x, 0), temp],[round(x, 0), bat],[round(x, 0), rssi]]
	print (json.dumps( jsondata ))
