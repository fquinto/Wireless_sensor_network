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
$_SESSION['OS']=giveme_os();
?>
<h1><?php echo INFOOS_MESSAGE; ?> <small><?php echo DETECTED_MSG; ?></small></h1>
<br>
<h2><?php echo $_SESSION['OS'];?></h2>
  <br><br>
  <?php echo( INFO_SERVER_TESTED_MESSAGE2 ); ?> <strong>LINUX</strong><br>
  <?php echo( INFO_SERVER_TESTED_MESSAGE2 ); ?> <strong>WINDOWS</strong><br>
</div>

    <?php include("../javascript.php"); ?>

</body>
</html>