#!C:\Python32\python.exe -u
#!/usr/bin/env python
# Import modules for CGI handling
import cgi, cgitb
import serial
import sys
import time

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
veces = form.getvalue('veces')

lang_msg = form.getvalue('lang')

if (str(lang_msg) == "undefined" or str(lang_msg) == "None"):
	lang_msg = "es"

if (lang_msg == "es"):
	error_msg = "ERROR: no puedo abrir el puerto!"
	info_msg = "Mensaje recibido: "
if (lang_msg == "ca"):
	error_msg = "ERROR: no puc obrir el port!"
	info_msg = "Missatge rebut: "
if (lang_msg == "en"):
	error_msg = "ERROR: Could not open port!"
	info_msg = "Message received: "

print ("Content-Type: text/javascript\n")
try:
	#ser = serial.Serial(port=puerto, baudrate=velocidad, timeout=2, bytesize=databit, stopbits=stopbit, parity=paridad, rtscts=hard, xonxoff=soft)
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
	print (error_msg)
else:
	if (veces == None):
		veces = 1

	if ((veces == "endless") or (veces == "sin fin") or (veces == "sense fi")):
		endless = 1
	else:
		endless = 0
		veces = int(veces)

	while True:
		data = ser.readline()
		if (len(data)>0):
			print (info_msg+data.decode('utf-8'))
			print ("<br>")
			break
		if (endless == 0):
			if (veces == 1):
				break
			veces = veces - 1
		sys.stdout.flush()
		time.sleep(0.5)
