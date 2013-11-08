<?php
if (!isset($_SESSION)) {
	session_start();
}
include("../init.php");
?><?php
writeheader(HOME_DESCRIP,KEYWORDS_MESSAGE);
?>
</head>
<body>
<?php include("../menu.php"); ?>
<div class="container">
<?php
$version="";
/*
$x = (explode('/', $_SERVER['PHP_SELF']));
array_pop ($x);
$D = array_pop ($x);
$host='http://'.$_SERVER['SERVER_NAME'].'/'.$x[1].'/'.$D.'/'.'phpinfo_all.php';
$file = @file_get_contents($host);
$start = explode("<h1 class=\"p\">",$file,1000);
if(count($start) < 2){
//echo "MySQL is not on this server.";
}else{
$again = explode("PHP Version ",$start[1],1000);
$last_time = explode("</h1>",$again[1],1000);
$version=$last_time[0];
//echo "MySQL Version: <b>".$last_time[0]."</b>";
}
*/
$version=phpversion();
?>
<h1><?php echo PHPSERVER_MSG; ?> <small><?php echo DETECTED_MSG; ?></small></h1>
<br>
<h2>PHP <?php echo $version;?></h2>
  <br><br>
  <?php echo( INFO_SERVER_TESTED_MESSAGE2 ); ?> <strong>LINUX: 5.3.10-1ubuntu3.4</strong><br>
  <?php echo( INFO_SERVER_TESTED_MESSAGE2 ); ?> <strong>WINDOWS: 5.4.3</strong><br>
</div>

    <?php include("../javascript.php"); ?>

</body>
</html>