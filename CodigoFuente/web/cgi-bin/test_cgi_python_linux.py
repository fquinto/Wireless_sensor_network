#!/usr/bin/python
# Import modules for CGI handling 
import cgi, cgitb

print "Content-type: text/html\n\n"
print """
<!DOCTYPE html>

<head><title>Test CGI Python Linux</title></head>

<body>

  <h3> Test CGI Python Linux </h3>
"""

form = cgi.FieldStorage()
message = form.getvalue("message", "(no message)")

print """

  <p>Previous message: %s</p>

  <p>form

  <form method="post" action="test_cgi_python_linux.py">
    <p>message: <input type="text" name="message"/></p>
  </form>
</body>
</html>
""" % cgi.escape(message)