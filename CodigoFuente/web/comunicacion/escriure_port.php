<?php
if (!isset($_SESSION)) {
	session_start();
}
include("../init.php");
?><?php
writeheader(HOME_DESCRIP,KEYWORDS_MESSAGE);
?>
	<script>
	  function foco(){
	    document.enviar.q.focus()
	    document.enviar.q.select() 
	  }
	</script>
	<link rel="stylesheet" type="text/css" href="../css/button.css" />
</head>
<body onload="foco();">
<?php include("../menu.php"); ?>
<div class="container">
<?php if (isset($_SESSION['puerto']) && $_SESSION['puerto']!="" && isset($_SESSION['OS']) && $_SESSION['OS']!="")
{ ?>
    <?php echo INFOOS_MESSAGE; ?> <strong><?php echo $_SESSION['OS'];?></strong><br>
    <?php echo PORT_SELECTED_MESSAGE; ?> <strong><?php echo $_SESSION['puerto'];?></strong><br>
	<br><br>
	<form name="enviar" method="get" action="enviar.php">
	<?php echo WRITE_MESSAGE; ?> <input name="q" id="q" type="text" size="10" maxlength="10" value="<?php echo (isset($_SESSION['mensaje'])) ? $_SESSION['mensaje'] : '' ?>" />
	<input type="submit" class="button" value="<?php echo SEND_BUTTON_MESSAGE; ?>" />
	</form>
<?php
} else {
	echo ERROR_BEFOREWRITE_MESSAGE;
} ?>
</div>

    <?php include("../javascript.php"); ?>

</body>
</html>