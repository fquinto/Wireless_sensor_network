#!/usr/bin/python

import sys
import serial
import cgi, cgitb
import json

#-----------------------------------------------------------------------------
# Comprueba si el puerto serie es escribible
# ENTRADAS:
#   -port : puertos a comprobar
#
# DEVUELVE: 
#    formato: JSON: si (1) o no (0)
#-----------------------------------------------------------------------------

puerto_escribible=0

form = cgi.FieldStorage() # instantiate only once!
port = form.getvalue('port')

try:
	#-- Abrir puerto serie
	s = serial.Serial(port)

	puerto_escribible=1

	#-- Cerrar puerto
	s.close()

except:
	pass

print "Content-Type: application/json\n"
if (puerto_escribible == 0):
	jsondata = [ 0 ]
else:
	jsondata = [ 1 ]
print json.dumps( jsondata )