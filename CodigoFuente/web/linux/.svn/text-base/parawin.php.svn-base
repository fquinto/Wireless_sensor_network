 
<?php
// Acceso mediante PHP al puerto serie
$serproxy=true;
if ($serproxy) {
// Este código debe utilizarse en combinación con serproxy
// (http://www.lspace.nildram.co.uk/freeware.html)
$fp = fsockopen ("localhost", 5331, $errno, $errstr, 10);
if (!$fp) {
echo "$errstr ($errno)";
 } else {
 $string ="3";
 fputs ($fp, $string );
 $line="";
 $line = trim(fgets($fp));
 echo "<br>".$line;
 echo "<br><form action='serie.php'><input type='submit' value='CAMBIAR LED'/></form>";

 fclose ($fp);
 }
 }
 ?>