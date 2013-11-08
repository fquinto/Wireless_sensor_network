<?php
include "php_serial.class.php";

// Let's start the class
$serial = new phpSerial;

// First we must specify the device. This works on both linux and windows (if
// your linux serial device is /dev/ttyS0 for COM1, etc)
$serial->deviceSet("/dev/ttyUSB0");

// We can change the baud rate
$serial->confBaudRate(9600);

// Then we need to open it
$serial->deviceOpen();

// To write into
$serial->sendMessage("1");

// Or to read from
//$read = $serial->readPort();

// If you want to change the configuration, the device must be closed
//$serial->deviceClose();

// etc...
?>
