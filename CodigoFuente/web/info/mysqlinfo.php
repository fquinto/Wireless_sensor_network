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
$x = (explode('/', $_SERVER['PHP_SELF']));
array_pop ($x);
$D = array_pop ($x);
$host='http://'.$_SERVER['SERVER_NAME'].'/'.$x[1].'/'.$D.'/'.'phpinfo_all.php';
$file = @file_get_contents($host);
$start = explode("<h2><a name=\"module_mysql\">mysql</a></h2>",$file,1000);
if(count($start) < 2){
//echo "MySQL is not on this server.";
}else{
$again = explode("<tr><td class=\"e\">Client API version </td><td class=\"v\">",$start[1],1000);
$last_time = explode(" </td></tr>",$again[1],1000);
$version=$last_time[0];
//echo "MySQL Version: <b>".$last_time[0]."</b>";
} ?>
<h1><?php echo MYSQLSERVER_MSG; ?> <small><?php echo DETECTED_MSG; ?></small></h1>
<br>
<h2>MySQL <?php echo $version;?></h2>
  <br><br>
  <?php echo( INFO_SERVER_TESTED_MESSAGE2 ); ?> <strong>LINUX: 5.1.58</strong><br>
  <?php echo( INFO_SERVER_TESTED_MESSAGE2 ); ?> <strong>WINDOWS: mysqlnd 5.0.8-dev - 20102224 - $Revision: 310735 $</strong><br>
</div>

    <?php include("../javascript.php"); ?>

</body>
</html>

