<?php

define('ENABLE_LOCAL_WEB',1); // 0=online   1=local
/*
 * Esto se debe a que en local uso: 127.0.0.1/proyectoweb y en online proyectoweb.com entonces en online "subo" 0 directorios y en local 1.
*/

// language code
// NOTA: para los idiomas también mirar el languages.php
$valid_langs = array('en','es','ca');
if (!empty($_GET['lang']))
{
	// primarily look for the lang parameter
	$lang = $_GET['lang'];
}
elseif (!empty($_SESSION['lang']))
{
	// if not look for the session lang
	$lang = $_SESSION['lang'];
}
// check if $lang is set and valid
if (isset($lang) && in_array($lang, $valid_langs))
{
	include __path(ENABLE_LOCAL_WEB).'lang/' . $lang . '/index.php';

	// set session lang for later
	$_SESSION['lang'] = $lang;
}
else
{
	// else use default: ES
	$lang="es";
	include __path(ENABLE_LOCAL_WEB).'lang/' . $lang . '/index.php';
	$_SESSION['lang'] = $lang;
}
?>
<?php
	//enlace dinámico	
	function __path($localdir = 0) {
		//el valor inicial de $rp era: $rp='./' pero esto generaba un warning en la validacion del HTML5
		$rp = ''; $s = explode(basename($_SERVER['PHP_SELF']), $_SERVER['PHP_SELF'], 2); $n = trim($s[0], '/') ? count(explode('/', trim($s[0], '/'))) - $localdir : 0; for ($i = 0; $i < $n; $i++) $rp .= '../'; return $rp;
	}
	
	//funcion para el enlace de los idiomas
	function enlaceidioma($idiomas,$idiomadestino,$entorno) {
		//ENTORNO: 0=internet   1=local
		$array1 = $idiomas;
		$array2 = array($idiomadestino);
		$result = array_diff($array1, $array2);
		$final="";
		$encontrado=0;
		foreach ($result as $value) {
			$pos = strpos($_SERVER['REQUEST_URI'],"/".$value."/");
			if($pos === false) {
				// no encontrado, mirar entorno
				if ($entorno) {
					//local
					//$final = str_replace("qrcode","qrcode/".$idiomadestino,$_SERVER['REQUEST_URI']);
					$pos2 = strpos(substr($_SERVER['REQUEST_URI'],1),"/")+1;
					$final = substr($_SERVER['REQUEST_URI'],0,$pos2+1) . $idiomadestino . substr($_SERVER['REQUEST_URI'],$pos2);
				} else {
					//internet
					$final = "/".$idiomadestino.$_SERVER['REQUEST_URI'];
				}
			}
			else {
				// encontrado
				$valor=$value;
				$encontrado=1;
			}
	
		}
		$pos = strpos($_SERVER['REQUEST_URI'],"/".$idiomadestino."/");
		if($pos === false) {
			// no encontrado
		} else {
			// encontrado
			$final = "";
			$encontrado=0;
		}
		if ($encontrado) {
			$final = str_replace("/".$valor."/","/".$idiomadestino."/",$_SERVER['REQUEST_URI']);
		}
	
		return $final;
	}
?>
<?php
function writeheader($description, $keywords) {
?>
<!DOCTYPE HTML>
<html lang="<?php echo $_SESSION['lang']; ?>">
  <head>
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <title><?php echo title(); ?> - UPC</title>
    <meta name="author" content="Fran Quinto" >
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta name="description" content="<?=$description?>" />
    <meta name="keywords" content="<?=$keywords?>" />
    <meta name="geo.region" content="ES-CT" />
    <meta name="geo.placename" content="UPC, Barcelona" />
    <meta name="geo.position" content="41.388714;2.111907" />
    <meta name="ICBM" content="41.388714, 2.111907" />

    <!-- Le styles -->
    <link rel="stylesheet" href="<?php echo __path(ENABLE_LOCAL_WEB); ?>css/bootstrap.css">
    <link href="<?php echo __path(ENABLE_LOCAL_WEB); ?>css/bootstrap-responsive.css" rel="stylesheet">

    <!-- Le HTML5 shim, for IE6-8 support of HTML5 elements -->
    <!--[if lt IE 9]>
      <script src="http://html5shim.googlecode.com/svn/trunk/html5.js"></script>
    <![endif]-->

    <!-- Le fav and touch icons -->
    <link rel="shortcut icon" href="<?php echo __path(ENABLE_LOCAL_WEB); ?>imagen/favicon.ico" type="image/x-icon">
    <link rel="apple-touch-icon-precomposed" sizes="144x144" href="<?php echo __path(ENABLE_LOCAL_WEB); ?>imagen/apple-touch-icon-144-precomposed.png">
    <link rel="apple-touch-icon-precomposed" sizes="114x114" href="<?php echo __path(ENABLE_LOCAL_WEB); ?>imagen/apple-touch-icon-114-precomposed.png">
    <link rel="apple-touch-icon-precomposed" sizes="72x72" href="<?php echo __path(ENABLE_LOCAL_WEB); ?>imagen/apple-touch-icon-72-precomposed.png">
    <link rel="apple-touch-icon-precomposed" href="<?php echo __path(ENABLE_LOCAL_WEB); ?>imagen/apple-touch-icon-57-precomposed.png">
<?php
} // end writeheader
?>
<?php

function title() {
	$x = (explode('/', $_SERVER['PHP_SELF']));
	array_pop ($x);
	$estado_menu = array_pop ($x);
	switch ($estado_menu) {
		case 'configuracion':
			$titulo = CONFIGURACION_MESSAGE;
			;
			break;
		case 'comunicacion':
			$titulo = COMUNICACION_MESSAGE;
			;
			break;
		case 'monitorizacion':
			$titulo = MONITORIZATION_MESSAGE;
			;
			break;
		case 'info':
			$titulo = 'Info';
			;
			break;
		case 'about':
			$titulo = ABOUT_MESSAGE;
			;
			break;
		case 'contact':
			$titulo = CONTACT_MESSAGE;
			;
			break;
		case 'cgi-bin':
			$titulo = 'cgi-bin';
			;
			break;
		default:
			$titulo = 'Home';
		;
		break;
	}
	return $titulo;
}

function giveme_os() {
  $OS = "UNKNOW_OS";
  if (strtoupper(substr(PHP_OS, 0, 3)) === "WIN") {
      $OS="WINDOWS";
  }
  if (strtoupper(substr(PHP_OS, 0, 3)) === "LIN") {
      $OS="LINUX";
  }
  return $OS;
}

function giveme_port($OS) {
  $port = "UNKNOW_PORT";
  if ($OS=="LINUX") {
    //prog. per Linux
    $texto = exec("dmesg | grep tty");
    //$texto = "[    1.215306] 00:09: ttyS0 at I/O 0x3f8 (irq = 4) is a 16550A"; // FOR DEBUG
    //$texto = "[10619.182208] usb 2-1.3: FTDI USB Serial Device converter now attached to ttyUSB0"; // FOR DEBUG
    $h1count = preg_match_all('/ (tty(S|USB|ACM)[0-9])/',$texto,$patterns);
    //echo $texto . "<br><br>"; // FOR DEBUG
    //var_dump($patterns); // FOR DEBUG
    //echo "<br><br>[1][0]=###".$patterns[1][0] . "###<br><br>"; // FOR DEBUG
    if(isset($patterns[1][0])){
      $port = "/dev/".$patterns[1][0];
    } else {
      $port = "ERROR";
    }
  }
  if ($OS=="WINDOWS") {
    //prog. per Windows
    $osys = strtolower($OS);
    $jsonurl = url_completa('../cgi-bin/givemeports_'.$osys.'.py?id=1');
    $json = file_get_contents($jsonurl,0,null,null);
    $json_output = json_decode($json,true);
    if ($json_output != "") {
      $port = $json_output[0]['optionValue']; // el primero del array
      if ($port == "") {
        $port = "COM1";
      }
    } else {
        $port = "COM1";
    }
  }
  if ($OS=="UNKNOW_OS") {
    $port = $OS; // $port = UNKNOW_OS
  }
return $port;
}

function writable_port($port) {
  // return 1 when writable, return 0 when error or not writable
  $devuelve = 0;
  $os = strtolower(giveme_os());
  $jsonurl = url_completa('../cgi-bin/check_port_'.$os.'.py?port='.$port); //$PATH=http://127.0.0.1/serie/cgi-bin/check_port_linux.py
  $json = file_get_contents($jsonurl,0,null,null);
  $json_output = json_decode($json);
  $devuelve = $json_output[0];
  return $devuelve;
}

function check_if_exist_port($port) {
  // return 1 when exits, return 0 when no exists serial port
  // solo para WINDOWS!!
  $devuelve = 0;
  $os = strtolower(giveme_os());
  $jsonurl = url_completa('../cgi-bin/portsnobusy_'.$os.'.py?id=1');
  $json = file_get_contents($jsonurl,0,null,null);
  $json_output = json_decode($json,true);
  foreach($json_output as $puertos)
  {
    if ( $puertos['optionValue'] == $port) {
      $devuelve=1;
    }
  }
  return $devuelve;
}

/*
* Function strallpos
* Returns all positions of the search term in the
* string as an array
*/
function strallpos($haystack,$needle,$offset = 0) {
	$result = array();
	// Loop through the $haystack/string starting at offset
	for($i = $offset; $i<strlen($haystack); $i++){
		$pos = strpos($haystack,$needle,$i);
		if($pos !== FALSE){
			$offset =  $pos;
			if($offset >= $i){
				$i = $offset;
				// Add found results to return array
				$result[] = $offset;
			}
		}
	}
	return count($result);
}

/*
 * Function url_completa
 * Return all complete URL link, like: http://127.0.0.1/serie/cgi-bin/lectura_graph.py
 * If you use ../ you can move inside path and this functions returns correct position
 */
function url_completa ($rel_path) {
	$abs_path = substr($_SERVER['PHP_SELF'],0,strrpos($_SERVER['PHP_SELF'],"/"));
	//if(substr($abs_path,-1) != '/') $abs_path .= '/'; //siempre acabará con barra /
	$searching = "../";
	//num. veces que hemos encontrado '../' en $rel_path
	$veces = strallpos($rel_path,$searching);
	$rel_path=substr($rel_path,($veces*strlen($searching)));
	for ($i = 0; $i < $veces; $i++) {
		$abs_path = substr($abs_path,0,strrpos($abs_path,"/"));
	}
	return 'http://'.$_SERVER['HTTP_HOST'].$abs_path.'/'.$rel_path;
}
?>