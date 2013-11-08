<?php
//PHP call out to cgi-script example
//$data = file_get_contents("http://127.0.0.1/serie/cgi-bin/lectura.py",0);
$PATH="http://".$_SERVER['HTTP_HOST']."/serie/cgi-bin/lectura.py";
$data = file_get_contents($PATH,0);
echo $data;
?>