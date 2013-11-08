#!/usr/bin/python
# Import modules for CGI handling

# Author     Fecha         Version
# F.Quinto   2012-09-03    1.0

import cgi, cgitb
import sys, serial, time

# CALL using browser:
# http://127.0.0.1/serie/cgi-bin/com_linux.py?puerto=/dev/ttyS32&velocidad=9600&databit=8&stopbit=1&paridad=none&control=none&veces=1&destino_msg=AP&rw=R&address=50&data=000&lang=es&debug=1


# Create instance of FieldStorage
form = cgi.FieldStorage() # instantiate only once!

# VARIABLES ===============================

# configuracion puerto serie
puerto = form.getvalue('puerto')
velocidad = form.getvalue('velocidad')
databit = form.getvalue('databit')
stopbit = form.getvalue('stopbit')
paridad = form.getvalue('paridad')
control = form.getvalue('control')
lang_msg = form.getvalue('lang')
veces = form.getvalue('veces')
debug = form.getvalue('debug')

# mensaje
cabecera = form.getvalue('destino_msg')
rw_msg = form.getvalue('rw')
address_msg = form.getvalue('address')
data_msg = form.getvalue('data')

# END VARIABLES ===============================

# control de existencia de lang_msg, por defecto spanish
if (str(lang_msg) == "undefined" or str(lang_msg) == "None"):
	lang_msg = "es"

# set de mensajes de error
if (lang_msg == "es"):
	msg_enviado = "Mensaje enviado: "
	msg_recibido = "Mensaje recibido: "
	error_msg = "ERROR: no puedo abrir el puerto!<br>INFO: "
	error_com = "ERROR: comunicaciones!<br>INFO: "
	error_txt = "ERROR: no puedo abrir el puerto!"
if (lang_msg == "ca"):
	msg_enviado = "Missatge enviat: "
	msg_recibido = "Missatge rebut: "
	error_msg = "ERROR: no puc obrir el port!<br>INFO: "
	error_com = "ERROR: comunicacions!<br>INFO: "
	error_txt = "ERROR: no puc obrir el port!"
if (lang_msg == "en"):
	msg_enviado = "Message sent: "
	msg_recibido = "Message received: "
	error_msg = "ERROR: could not open port!<br>INFO: "
	error_com = "ERROR: communicating!<br>INFO: "
	error_txt = "ERROR: could not open port!"

# databit
if (databit == "5"):
	databit = serial.FIVEBITS
if (databit == "6"):
	databit = serial.SIXBITS
if (databit == "7"):
	databit = serial.SEVENBITS
if (databit == "8"):
	databit = serial.EIGHTBITS

# stopbit
if (stopbit == "1"):
	stopbit = serial.STOPBITS_ONE
if (stopbit == "1.5"):
	stopbit = serial.STOPBITS_ONE_POINT_FIVE
if (stopbit == "2.0"):
	stopbit = serial.STOPBITS_TWO

# paridad
if (paridad == "none"):
	paridad = serial.PARITY_NONE
if (paridad == "odd"):
	paridad = serial.PARITY_ODD
if (paridad == "even"):
	paridad = serial.PARITY_EVEN

# control
if (control == "none"):
	hard=0
	soft=0
if (control == "rts/cts"):
	hard=1
	soft=0
if (control == "xon/xoff"):
	hard=0
	soft=1

# cabecera
if (cabecera == "AP"):
	cabecera = chr(0x41)
if (cabecera == "ED"):
	cabecera = chr(0x42)
if (cabecera == "FG"):
	cabecera = chr(0x43)
if (cabecera == "undefined"):
	cabecera = chr(0x43)

# control de recepcion de rw_msg
if ( rw_msg == "undefined" or rw_msg == None or len(rw_msg)!=1 ):
	rw_msg = "R"

# control de recepcion de address_msg
if ( address_msg == "undefined" or address_msg == None or len(address_msg)!=2 ):
	address_msg = "10"

# control de recepcion de data_msg
if ( data_msg == "undefined" or data_msg == None or len(data_msg)!=3 ):
	data_msg = "000"

# control de lectura, repeticiones (veces)
if ( veces == "undefined" or veces == None ):
	veces = 1
else:
	veces = int(veces)

# construccion del mensaje
message = rw_msg + address_msg + data_msg

# Control del mensaje: Avoid script injection escaping the user input
message = cgi.escape(message)

# Control del debug
if ( debug == "undefined" or debug == None ):
	debug = 0
else:
	debug = int(debug)

print "Content-Type: text/javascript\n"
# print "Content-Type: text/html\n"
if ( debug==1 ):
		print "Language lang_msg: <br>"
		print lang_msg
try:
	#initialization and open the port
	ser = serial.Serial()
	ser.port = puerto
	ser.baudrate = velocidad
	ser.timeout = 2 #timeout block read
	ser.writeTimeout = 2 #timeout for write
	ser.parity = paridad
	ser.stopbits = stopbit
	ser.bytesize = databit
	ser.rtscts = hard
	ser.xonxoff = soft
	# Open serial port
	ser.open()
	if ( debug==1 ):
		print "OPENED!<br>"

except Exception, e:
	if ( debug==1 ):
		print "ERROR!<br>"
	print error_msg + str(e)
	exit()

if ser.isOpen():
	try:
		ser.flushInput() #flush input buffer, discarding all its contents
		ser.flushOutput()#flush output buffer, aborting current output 
			    #and discard all that is in buffer

		# === ENVIO =================================
		if ( debug==1 ):
			print "ENVIANDO...<br>"
		# escribo cabecera por puerto serie
		ser.write(cabecera)
		
		# espero (segundos)
		time.sleep(0.15)
		
		# escribo mensaje por puerto serie
		ser.write(message)
		
		# escribo salto de linea por puerto serie
		ser.write("\r")
		
		# visualizo mensaje enviado
		print msg_enviado+cabecera+message
		# ===========================================
		
		if ( rw_msg=="R" ):
			# === RECIBO ================================
			if ( debug==1 ):
				print "RECIBIENDO...<br>"
			
			# espero (segundos) para dar tiempo a recibir los datos
			time.sleep(0.25)
			
			# borro variable message
			message = ""
			
			# bucle lectura
			while True:
				data = ser.readline()
				if (len(data)>0):
					message = data
					break
				if (veces == 1):
					break
				veces = veces - 1
				sys.stdout.flush()
				time.sleep(0.5)

			# visualizo mensaje recibido
			print "<br>"
			print msg_recibido+message
			# ===========================================
		
		# cierro el puerto serie
		ser.close()
		
		if ( debug==1 ):
			print "FINAL!<br>"

	except Exception, e1:
		print error_com + str(e1)
else:
    print error_txt
