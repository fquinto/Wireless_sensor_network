<?php
if (!isset($_SESSION)) {
	session_start();
}
include("../init.php");

header('Content-Encoding: gzip', true);
header ("content-type: image/svg+xml", true);
?>
<?php
// get contents of a image file (SVG) into a string
$filename = "../imagen/esquema_mensajeria.svg";
$handle = fopen($filename, "r");

// eliminar 114 bytes iniciales
//fseek($handle, 114);

// leer contenido
$contents = fread($handle, filesize($filename));

// set sistema operativo
if (!isset($_SESSION['OS'])) {
  $os = "UNDEFINED";
} else {
  $os = $_SESSION['OS'];
}
$contents = str_replace ( "#SISTEMAOPERATIVO#" , $os , $contents );

// set apache version
if (!isset($_SERVER['SERVER_SOFTWARE'])) {
  $apache_version = "UNDEFINED";
} else {
  $apache_version = $_SERVER['SERVER_SOFTWARE'];
}
$contents = str_replace ( "#APACHE_VERSION#" , $apache_version , $contents );

// set php version
$contents = str_replace ( "#PHP_VERSION#" , phpversion() , $contents );

// set python version
if (isset($_SESSION['OS']) && $_SESSION['OS']=="LINUX")
{
  $PATH = url_completa('../cgi-bin/version_linux_installed.py');
}
if (isset($_SESSION['OS']) && $_SESSION['OS']=="WINDOWS")
{
  $PATH = url_completa('../cgi-bin/version_windows_installed.py');
}
$version_python = @stripslashes( @join( @file( $PATH ),"" ) );
if ($version_python==NULL) {
  $version_python = "UNDEFINED";
}
$contents = str_replace ( "#PYTHON_VERSION#" , $version_python , $contents );

// set serial port selected
if (!isset($_SESSION['puerto'])) {
  $serialport_selected = "UNDEFINED";
} else {
  $serialport_selected = $_SESSION['puerto'];
}
$contents = str_replace ( "#SERIAL_PORT_SELECTED#" , $serialport_selected , $contents );

// set serial port configuration
if (!isset($_SESSION['velocidad'])) {
  $config = "UNDEFINED";
} else {
  $config = $_SESSION['velocidad'] . " " . $_SESSION['databit'] . " " . $_SESSION['paridad'] . " " . $_SESSION['stopbit'] . " " . $_SESSION['control'];
}
$contents = str_replace ( "#CONFIGURATION_SERIAL_PORT#" , $config , $contents );

fclose($handle);
echo gzencode($contents, 9);
?>