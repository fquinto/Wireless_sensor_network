<?php
if (!isset($_SESSION)) {
  session_start();
}

include("../init.php");
include "../linux/php_serial.class.php";

// Let's start the class
$serial = new phpSerial;

$enable_exceptions=1; // 1 = ON  and 0 = OFF

if (isset($_SESSION['puerto']) && $_SESSION['puerto']!="" && isset($_SESSION['OS']) && $_SESSION['OS']!="")
{
	//envio normal
	if (isset($_GET['q']) && $_GET['q']!="")
	{
		$_SESSION['mensaje']=$_GET['q'];
		$enable_exceptions=0;
	}
	//envio ajax
	if (isset($_GET['q2']) && $_GET['q2']!="")
	{
		$_SESSION['mensaje']=$_GET['q2'];
	}
	
	
	try {
		$serial->deviceSet($_SESSION['puerto']);
	} catch (Exception $e) {
		if ($enable_exceptions) {
			echo 'Caught exception: <trong>',  $e->getMessage(), "</strong>\n";
			exit;
		}
	}
	
	if (isset($_SESSION['velocidad']))
	{
		try {
			$serial->confBaudRate($_SESSION['velocidad']);
		} catch (Exception $e) {
			if ($enable_exceptions) {
				echo 'Caught exception: <trong>',  $e->getMessage(), "</strong>\n";
				exit;
			}
		}
	}
	
	if (isset($_SESSION['databit']))
	{
		try {
			$serial->confCharacterLength($_SESSION['databit']);
		} catch (Exception $e) {
			if ($enable_exceptions) {
				echo 'Caught exception: <trong>',  $e->getMessage(), "</strong>\n";
				exit;
			}
		}
	}
	
	if (isset($_SESSION['paridad']))
	{
		try {
			$serial->confParity($_SESSION['paridad']);
		} catch (Exception $e) {
			if ($enable_exceptions) {
				echo 'Caught exception: <trong>',  $e->getMessage(), "</strong>\n";
				exit;
			}
		}
	}
	
	if (isset($_SESSION['stopbit']))
	{
		try {
			$serial->confStopBits($_SESSION['stopbit']);
		} catch (Exception $e) {
			if ($enable_exceptions) {
				echo 'Caught exception: <trong>',  $e->getMessage(), "</strong>\n";
				exit;
			}
		}
	}
	
	if (isset($_SESSION['control']))
	{
		try {
			$serial->confFlowControl($_SESSION['control']);
		} catch (Exception $e) {
			if ($enable_exceptions) {
				echo 'Caught exception: <trong>',  $e->getMessage(), "</strong>\n";
				exit;
			}
		}
	}
		
	try {
		$serial->deviceOpen();
	} catch (Exception $e) {
		if ($enable_exceptions) {
			echo 'Caught exception: <trong>',  $e->getMessage(), "</strong>\n";
			exit;
		}
	}
	
	try {
		$serial->sendMessage($_SESSION['mensaje']."\r");
	} catch (Exception $e) {
		if ($enable_exceptions) {
			echo 'Caught exception: <trong>',  $e->getMessage(), "</strong>\n";
			exit;
		}
	}
	
	//envio normal
	if (isset($_GET['q']) && $_GET['q']!="")
	{
		header("Location: escriure_port.php");
		exit;
	}
	//envio ajax
	if (isset($_GET['q2']) && $_GET['q2']!="")
	{
		usleep(1000);
		echo "<br><br>\n".SENT_MESSAGE . " <strong>" . $_SESSION['mensaje'] . "</strong>";
		usleep(1000);
	}
	
}
?>