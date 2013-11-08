<?php
//PHP call out to cgi-script example
// NOTA: No usar este ejemplo, depende del Sistema Operativo
$result = exec("python /media/DATOS/UPC/Proyecto/web/cgi-bin/lectura.py", $out1);
$out2 = join( "\n", $out1 );
print($out2);
?>