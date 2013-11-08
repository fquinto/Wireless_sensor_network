<?php
//PHP call out to cgi-script example
//echo @stripslashes( @join( @file( "http://127.0.0.1/serie/cgi-bin/lectura.py" ),"" ) );
$PATH="http://".$_SERVER['HTTP_HOST']."/serie/cgi-bin/lectura.py";

for ($i = 1; $i <= 8; $i++) {
    $var= @stripslashes( @join( @file( $PATH ),"" ) );
    $pieces = explode(",", $var);
    $valor = str_replace(array("\r\n", "\n", "\r"), '', $pieces[1]);
    echo $valor;
}
?>