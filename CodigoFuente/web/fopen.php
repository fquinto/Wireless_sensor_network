<?php


/* Simple interaction between Arduino and PHP environment
*/

//Set up serial open
$fp =fopen("/dev/ttyUSB0", "w");

//check the GET actions variable to see if something needs to be done
if (isset($_GET['action'])) {
    //Action has been requested

    //Issue the command we wish to send to the Arduino
    if ($_GET['action'] == "on") {
        //Turn LED on - for this simple script we are just looking for either a 1 or 0 
        fwrite($fp, 1);
    
    } else if ($_GET['action'] == "off") {
        //Turn LED off
        fwrite($fp, 0);

    }
    
    //We're done, so close the serial port again
    fclose($fp);

}


?><!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" 
"http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1">
<title>Arduino LED control</title>
</head>
<body>
http://blog.datasingularity.com/?p=50
<h1>LED Control system - Arduino Interface</h1>
<p><a href="<?=$_SERVER['PHP_SELF'] . "?action=on" ?>">
Turn LED On.</a></p>
<p><a href="<?=$_SERVER['PHP_SELF'] . "?action=off" ?>">
Turn LED Off.</a></p>
</body>
</html>