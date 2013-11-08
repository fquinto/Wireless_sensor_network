<?php
if (!isset($_SESSION)) {
  session_start();
}

switch ($_GET['quitar']) {
	case "puerto":
		$_SESSION['puerto'] = NULL;
		unset($_SESSION['puerto']);
	break;
	case "os":
		$_SESSION['OS'] = NULL;
		unset($_SESSION['OS']);
	break;
	case "velocidad":
		$_SESSION['velocidad'] = NULL;
		$_SESSION['databit'] = NULL;
		$_SESSION['paridad'] = NULL;
		$_SESSION['stopbit'] = NULL;
		$_SESSION['control'] = NULL;
		unset($_SESSION['velocidad']);
		unset($_SESSION['databit']);
		unset($_SESSION['paridad']);
		unset($_SESSION['stopbit']);
		unset($_SESSION['control']);
	break;
	default:
		// Destruye todas las variables de la sesión
		session_unset();
		// Finalmente, destruye la sesi&oacute;n
		session_destroy();
	break;
}
if (isset($_GET['ir']) && $_GET['ir']!="") {
  header("Location: ".$_GET['ir'].".php");
} else {
  header("Location: ../ ");
}
exit;
?>