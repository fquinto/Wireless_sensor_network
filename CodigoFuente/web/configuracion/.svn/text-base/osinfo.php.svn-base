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
<h1><?php echo MANUAL_MESSAGE; ?> <small><?php echo DETECT_OS_MESSAGE; ?></small></h1>
<br>
<h2><?php echo ucfirst(INFOOS_MESSAGE).":"; ?> <strong><?php echo $_SESSION['OS']; ?></strong></h2>
<br><br>
<a class="btn" href="javascript:history.back(1)"><i class="icon-chevron-left"></i> <?php echo( GOBACK_MESSAGE );?></a>
<a class="btn" href="../"><i class="icon-home"></i> <?php echo( GOHOME_MESSAGE );?></a>
</div> <!-- /container -->

    <?php include("../javascript.php"); ?>

</body>
</html>