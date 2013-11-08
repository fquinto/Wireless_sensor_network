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
<h1><?php echo MANUAL_MESSAGE; ?> <small><?php echo DETECT_PORT_MESSAGE; ?></small></h1>
<?php
if ( isset($_SESSION['OS']) && ($_SESSION['OS']!="") )
  {
    $_SESSION['puerto'] = giveme_port($_SESSION['OS']);
?>
    <br>
    <h2><?php echo ucfirst(DETECTED_PORT_MESSAGE).":"; ?> <strong><?php echo $_SESSION['puerto']; ?></strong></h2>
    <br><br>
<?php
  } else {
?>
    <div class="alert alert-block alert-error fade in">
      <button type="button" class="close" data-dismiss="alert">×</button>
      <h4 class="alert-heading">ERROR</h4>
      <p><?php echo ERROR_OSNOT_DETECTED_MESSAGE; ?></p>
      <p>
        <?php if (!isset($_SESSION['OS']) || $_SESSION['OS']=="") { ?>
          <a class="btn btn-primary" href="../configuracion/osinfo.php"><?php echo( DETECT_OS_MESSAGE );?></a>
        <?php } ?>
      </p>
  </div>
<?php
  }
?>
<a class="btn" href="javascript:history.back(1)"><i class="icon-chevron-left"></i> <?php echo( GOBACK_MESSAGE );?></a>
<a class="btn" href="../"><i class="icon-home"></i> <?php echo( GOHOME_MESSAGE );?></a>
</div> <!-- /container -->

    <?php include("../javascript.php"); ?>

</body>
</html>