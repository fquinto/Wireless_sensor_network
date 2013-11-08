#!C:\Python32\python.exe -u
#!/usr/bin/env python

import cgi
#, cgitb
import cgitb; cgitb.enable()  # for troubleshooting

print ("Content-type: text/html")
print ("""
<!DOCTYPE html>

<head><title>Test CGI Python Windows</title></head>

<body>

  <h3> Test CGI Python Windows </h3>
""")

form = cgi.FieldStorage()
message = form.getvalue("message", "(no message)")

print ("""

  <p>Previous message: """, cgi.escape(message) ,"""</p>

  <p>form

  <form method="post" action="test_cgi_python_windows.py">
    <p>message: <input type="text" name="message"/></p>
  </form>
</body>
</html>
""")