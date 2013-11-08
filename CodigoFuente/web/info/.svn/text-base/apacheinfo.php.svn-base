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
<?php $version = $_SERVER['SERVER_SOFTWARE']; ?>
<h1><?php echo WEBSERVER_MSG; ?> <small><?php echo DETECTED_MSG; ?></small></h1>
<br>
<h2><?php echo $version;?></h2>
  <br><br>
  <?php echo( INFO_SERVER_TESTED_MESSAGE2 ); ?> <strong>LINUX: Apache/2.2.22 (Ubuntu)</strong><br>
  <?php echo( INFO_SERVER_TESTED_MESSAGE2 ); ?> <strong>WINDOWS: Apache/2.2.22 (Win32)</strong><br>
</div>

    <?php include("../javascript.php"); ?>

</body>
</html>