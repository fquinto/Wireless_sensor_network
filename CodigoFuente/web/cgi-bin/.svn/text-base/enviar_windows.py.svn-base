#!C:\Python32\python.exe -u
#!/usr/bin/env python
# Import modules for CGI handling 
import cgi, cgitb
import sys, serial, time

# Create instance of FieldStorage
form = cgi.FieldStorage() # instantiate only once!

# Get the first
#name = form.getfirst('name', 'empty')

# getlist() returns a list containing the
# values of the fields with the given name
#colors = form.getlist('color')

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
cabecera = form.getvalue('destino_msg')
if (cabecera == "AP"):
	cabecera = chr(0x41)
if (cabecera == "ED"):
	cabecera = chr(0x42)
if (cabecera == "FG"):
	cabecera = chr(0x43)
if (cabecera == "undefined"):
	cabecera = chr(0x43)

rw_msg = form.getvalue('rw')
if (rw_msg == "undefined" or rw_msg == None):
	rw_msg = "R"

address_msg = form.getvalue('address')
if (address_msg == "undefined" or address_msg == None):
	address_msg = "10"

data_msg = form.getvalue('data')
if (data_msg == "undefined" or data_msg == None):
	data_msg = "000"

message = rw_msg + address_msg + data_msg

lang_msg = form.getvalue('lang')

if (str(lang_msg) == "undefined" or str(lang_msg) == "None"):
	lang_msg = "es"

if (lang_msg == "es"):
	error_msg = "ERROR: no puedo abrir el puerto!"
	info_msg = "Mensaje enviado: "
if (lang_msg == "ca"):
	error_msg = "ERROR: no puc obrir el port!"
	info_msg = "Missatge enviat: "
if (lang_msg == "en"):
	error_msg = "ERROR: Could not open port!"
	info_msg = "Message sent: "

print ("Content-Type: text/html\n")
try:
	ser = serial.Serial(port=puerto, baudrate=velocidad, timeout=2, bytesize=databit, stopbits=stopbit, parity=paridad, rtscts=hard, xonxoff=soft)
# ser = serial.Serial(port='COM3', baudrate=9600, timeout=2, bytesize=serial.EIGHTBITS, stopbits=serial.STOPBITS_ONE, parity=serial.PARITY_NONE, rtscts=0, xonxoff=0)
except:
	print ("<html><body><p>",error_msg,"</p></body></html>")
else:
	ser.write(cabecera.encode())
	time.sleep(0.15)
	#if (len(message)>7):
		#ser.write(message[0:7].encode('utf-8'))
		#time.sleep(0.15)
		#ser.write(message[7:].encode('utf-8'))
	#else:
	ser.write(message.encode('utf-8'))
	if (len(message)<15):
		ser.write(b'\r')
	print ("<html><body><p>",info_msg+cabecera+message,"</p></body></html>")
	#time.sleep(2)
	#ser.close()

## tested on Arduino: abans treure el RESET (http://www.arduino.cc/playground/Main/DisablingAutoResetOnSerialConnection)