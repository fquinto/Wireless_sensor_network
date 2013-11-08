#!/usr/bin/python
# Import modules for CGI handling 
import cgi, cgitb
import serial
import sys
import time
ser = serial.Serial('/dev/ttyUSB0',9600)

print "Content-Type: text/javascript\n\n"
a=0
while a < 12:
    data = ser.readline()
    print "data: %s\n" % (data)
    sys.stdout.flush()
    time.sleep(1)
    a=a+1