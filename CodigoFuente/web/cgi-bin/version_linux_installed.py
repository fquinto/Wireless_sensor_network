#!/usr/bin/python
import sys
print "Content-type: text/html\n\n"
print("%s.%s.%s" % sys.version_info[:3])
