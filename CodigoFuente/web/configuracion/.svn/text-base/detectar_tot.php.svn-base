<?php
if (!isset($_SESSION)) {
	session_start();
}
include("../init.php");
?><?php
writeheader(HOME_DESCRIP,KEYWORDS_MESSAGE);
?>
	<meta http-equiv="Refresh" content="5;url=../" />
</head>
<body>
<?php include("../menu.php"); ?>
<div class="container">
<h1><?php echo( AUTO_MESSAGE ); ?> <small><?php echo( AUTODETECALL_MESSAGE ); ?></small></h1>
<?php
$_SESSION['OS'] = giveme_os();
$_SESSION['puerto'] = giveme_port($_SESSION['OS']);
?>
<h2>Control <small><?php echo INFOOS_MESSAGE; ?>:<strong> <?php echo $_SESSION['OS'];?></strong> · <?php echo PORT_SELECTED_MESSAGE; ?> <strong><?php echo $_SESSION['puerto'];?></strong></small></h2>
<?php
//configuració per defecte:
$_SESSION['velocidad']="9600";
$_SESSION['databit']="8";
$_SESSION['paridad']="none";
$_SESSION['stopbit']="1";
$_SESSION['control']="none";
?>
<br><?php echo( SPEED_MESSAGE ); ?> <strong><?php echo $_SESSION['velocidad'];?></strong>
<br><?php echo( DATABIT_MESSAGE ); ?> <strong><?php echo $_SESSION['databit'];?></strong>
<br><?php echo( PARITY_MESSAGE ); ?> <strong><?php echo $_SESSION['paridad'];?></strong>
<br><?php echo( STOPBIT_MESSAGE ); ?> <strong><?php echo $_SESSION['stopbit'];?></strong>
<br><?php echo( CONTROL_MESSAGE ); ?> <strong><?php echo $_SESSION['control'];?></strong>
<br><br>
<p><span class="label label-warning"><?php echo( WARNING_MESSAGE ); ?></span> <?php echo( REDIRECT_MESSAGE ); ?></p>
<br>
<a class="btn" href="javascript:history.back(1)"><i class="icon-chevron-left"></i> <?php echo( GOBACK_MESSAGE );?></a>
<a class="btn" href="../"><i class="icon-home"></i> <?php echo( GOHOME_MESSAGE );?></a>
</div> <!-- /container -->

    <?php include("../javascript.php"); ?>

</body>
</html>