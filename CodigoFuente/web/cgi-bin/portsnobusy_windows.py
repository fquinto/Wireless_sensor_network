#!C:\Python32\python.exe -u
#!/usr/bin/env python

import sys
import serial
import cgi, cgitb
import json
import winreg
import itertools

#-----------------------------------------------------------------------------
# Buscar puertos series disposibles y los encuentra, estén o no ocupados. 
# DEVUELVE: 
#    Una lista con todos los puertos encontrados. Cada elemento de la lista
#    es una tupla con el numero del puerto y el del dispositivo 
#-----------------------------------------------------------------------------

print ("Content-Type: application/json\n")
path = 'HARDWARE\\DEVICEMAP\\SERIALCOMM'
form = cgi.FieldStorage() # instantiate only once!
auto = form.getvalue('id')
try:
	key = winreg.OpenKey(winreg.HKEY_LOCAL_MACHINE, path)
except WindowsError:
	raise IterationError
if (auto == "1"):
	jsondata = []
	for i in itertools.count():
		try:
			val = winreg.EnumValue(key, i)
			nombre = str(val[1])
			aux = { 'optionValue':nombre, 'optionDisplay':nombre }
			jsondata.append(aux)
		except EnvironmentError:
			break
	print (json.dumps( jsondata ))
else:
	jsondata = [ {"optionValue": "COM1", "optionDisplay": "COM 1"}, {"optionValue": "COM2", "optionDisplay": "COM 2"}, {"optionValue": "COM3", "optionDisplay": "COM 3"}, {"optionValue": "COM4", "optionDisplay": "COM 4"}, {"optionValue": "COM5", "optionDisplay": "COM 5"}, {"optionValue": "COM6", "optionDisplay": "COM 6"}, {"optionValue": "COM7", "optionDisplay": "COM 7"}, {"optionValue": "COM8", "optionDisplay": "COM 8"}, {"optionValue": "COM9", "optionDisplay": "COM 9"}, {"optionValue": "COM33", "optionDisplay": "COM 33"}, {"optionValue": "COM34", "optionDisplay": "COM 34"}, {"optionValue": "COM35", "optionDisplay": "COM 35"}, {"optionValue": "CNCA0", "optionDisplay": "CNCA0"}, {"optionValue": "CNCB0", "optionDisplay": "CNCB0"}]
	print (json.dumps( jsondata ))
