<?php
if (!isset($_SESSION)) {
  session_start();
}

include "../linux/php_serial.class.php";

// Let's start the class
$_SESSION['clase_serial']=new phpSerial;
$serial = $_SESSION['clase_serial'];

if (isset($_SESSION['puerto']) && $_SESSION['puerto']!="" && isset($_SESSION['OS']) && $_SESSION['OS']!="")
{
	switch ($_GET['accion']) {
		case "abrir":
			// Then we need to open it
			$serial->deviceSet($_SESSION['puerto']);
			$serial->deviceOpen();
			$_SESSION['estado'] = 'abierto';
		break;
		case "leer":
			// Or to read from
			//$serial->deviceOpen();
			//$_SESSION['leido'] = $serial->readPort();
			$PATH="http://".$_SERVER['HTTP_HOST']."/serie/cgi-bin/lectura.py";
			$_SESSION['leido'] = file_get_contents($PATH,0);
			//$serial->deviceClose();
		break;
		case "escribir":
			// To write into
			if (isset($_POST['mensaje']) && $_POST['mensaje']!="")
			{
				$serial->deviceSet($_SESSION['puerto']);
				//$serial->deviceOpen();
				$serial->sendMessage($_POST['mensaje']);
				//$serial->deviceClose();
			}
		break;
		case "cerrar":
			$serial->deviceSet($_SESSION['puerto']);
			// If you want to change the configuration, the device must be closed
			$serial->deviceClose();
			$_SESSION['estado'] = 'cerrado';
		break;
		case "configura":
			// We can change the baud rate
			if (isset($_POST['velocidad']))
			{
				//$serial->confBaudRate($_POST['velocidad']);
				$_SESSION['velocidad'] = $_POST['velocidad'];
			}
			// We can change databit
			if (isset($_POST['databit']))
			{
				//$serial->confParity($_POST['databit']);
				$_SESSION['databit'] = $_POST['databit'];
			}
			// We can change parity
			if (isset($_POST['paridad']))
			{
				//$serial->confParity($_POST['paridad']);
				$_SESSION['paridad'] = $_POST['paridad'];
			}
			// We can change stopbit
			if (isset($_POST['stopbit']))
			{
				//$serial->confParity($_POST['stopbit']);
				$_SESSION['stopbit'] = $_POST['stopbit'];
			}
			// We can change control
			if (isset($_POST['control']))
			{
				//$serial->confFlowControl($_POST['control']);
				$_SESSION['control'] = $_POST['control'];
			}
		break;
		default:
		break;
	}
}
header("Location: configuracio.php");
exit;
?>