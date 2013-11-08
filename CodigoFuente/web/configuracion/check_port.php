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
<h1><?php echo( MANUAL_MESSAGE ); ?> <small><?php echo( CHECK_PORT_MESSAGE ); ?></small></h1>
<?php
if ( isset($_SESSION['puerto']) && $_SESSION['puerto']!="" && isset($_SESSION['OS']) && $_SESSION['OS']!="" )
{
?>
   <h2>Control <small><?php echo INFOOS_MESSAGE; ?>:<strong> <?php echo $_SESSION['OS'];?></strong> · <?php echo PORT_SELECTED_MESSAGE; ?> <strong><?php echo $_SESSION['puerto'];?></strong></small></h2>
<?php if ( $_SESSION['OS']=='LINUX' )
  {
    /*
    if (exec("stty -F " . $_SESSION['puerto']) === 0)
    {
      //echo "Puerto escribible!!<br>";
      $puerto_ok = $puerto_ok+1;
      echo 'A:'.$puerto_ok;
    }

    if (exec("echo 'test' >> ".$_SESSION['puerto']) == 0)
    {
      echo "Test 2: Puerto escribible!!<br>";
      $puerto_ok = $puerto_ok+1;
    }

    if (exec("ls -la ".$_SESSION['puerto']." | awk '{ print $1 }'") === "crwxrwxrwx")
    {
      echo "Permisos OK!!<br>";
      $puerto_ok = $puerto_ok+1;
    }
    */
    if ((exec("ls -la ".$_SESSION['puerto']." | awk '{ print $3 }'") === exec('whoami')) && (exec("ls -la ".$_SESSION['puerto']." | awk '{ print substr( $1, length($2), 3 ) }'")=== "crw") || (exec("ls -la ".$_SESSION['puerto']." | awk '{ print $1 }'") === "crwxrwxrwx"))
    {
      // puerto OK
?>
      <div class="alert alert-block alert-success fade in">
        <button type="button" class="close" data-dismiss="alert">×</button>
        <h4 class="alert-heading"><?php echo OK_MESSAGE; ?></h4>
        <?php echo ( CHECKOK_MESSAGE ); ?>
      </div>
<?php
    } else {
      // puerto KO
?>
      <div class="alert alert-block alert-error fade in">
        <button type="button" class="close" data-dismiss="alert">×</button>
        <h4 class="alert-heading">ERROR</h4>
        <?php echo ( ERROR_PORTNOT_DETECTED_MESSAGE ); ?>
<?php
        $puerto=exec("ls -la ".$_SESSION['puerto']);
        if (!empty($puerto)) {
          echo ( " " . ERROR_PERMISSIONS_PORT_MESSAGE . ":" )." <code>".exec("ls -la ".$_SESSION['puerto']).'</code><br>';
          echo ( ERROR_PERM_SOLUTION_MESSAGE . ": " );
          echo "<code>"."sudo chmod 777 " . $_SESSION['puerto'] . "</code><br>";
        } else {
?>
          <?php echo ( ERROR_NOTEXIST_PORT_MESSAGE ); ?><br><br>
          <a class="btn" href="quita.php?quitar=puerto&ir=<?php echo substr($_SERVER['SCRIPT_NAME'],0,-14)."configuracio";?>" title="<?php echo CHANGE_PORT_MESSAGE; ?>"><i class="icon-wrench"></i> <?php echo CHANGE_PORT_MESSAGE; ?></a>
<?php
	}
?>
      </div>
<?php
    }
  }
if ($_SESSION['OS']=='WINDOWS')
  {
    if ( writable_port($_SESSION['puerto'])==1 )
    {
      // puerto OK
?>
      <div class="alert alert-block alert-success fade in">
        <button type="button" class="close" data-dismiss="alert">×</button>
        <h4 class="alert-heading"><?php echo OK_MESSAGE; ?></h4>
        <?php echo ( CHECKOK_MESSAGE ); ?>
      </div>
<?php
    } else {
      // puerto KO
?>
      <div class="alert alert-block alert-error fade in">
        <button type="button" class="close" data-dismiss="alert">×</button>
        <h4 class="alert-heading">ERROR</h4>
        <?php echo ( ERROR_PORTNOT_DETECTED_MESSAGE ); ?>
		<?php //echo " " . ERROR_PORTBUSY_MESSAGE . "<br>" . ERROR_CATNOTEXIST_PORT_MESSAGE );?>
<?php

      if ( check_if_exist_port($_SESSION['puerto'])==1 )
      {

?>
        <?php echo " " . ERROR_PORTBUSY_MESSAGE; ?>
<?php
      } else {
?>
        <?php echo ( ERROR_NOTEXIST_PORT_MESSAGE ); ?><br><br>
        <a class="btn" href="quita.php?quitar=puerto&ir=<?php echo substr($_SERVER['SCRIPT_NAME'],0,-14)."configuracio";?>" title="<?php echo CHANGE_PORT_MESSAGE; ?>"><i class="icon-wrench"></i> <?php echo CHANGE_PORT_MESSAGE; ?></a>
<?php
      }
?>
      </div>
<?php
    }
  }
?>
<?php
} else { ?>
 <div class="alert alert-block alert-error fade in">
   <button type="button" class="close" data-dismiss="alert">×</button>
   <h4 class="alert-heading">ERROR</h4>
   <p><?php echo ERROR_BEFOREWRITE_MESSAGE; ?></p>
   <p>
     <?php if (!isset($_SESSION['OS']) || $_SESSION['OS']=="") { ?>
       <a class="btn btn-primary" href="../configuracion/osinfo.php"><?php echo( DETECT_OS_MESSAGE );?></a>
     <?php } elseif (!isset($_SESSION['puerto']) || $_SESSION['puerto']=="") { ?>
       <a class="btn btn-primary" href="../configuracion/detectar_port.php"><?php echo( DETECT_PORT_MESSAGE );?></a>
     <?php } ?>
   </p>
 </div>
<?php } ?>
<a class="btn" href="javascript:history.back(1)"><i class="icon-chevron-left"></i> <?php echo( GOBACK_MESSAGE );?></a>
<a class="btn" href="../"><i class="icon-home"></i> <?php echo( GOHOME_MESSAGE );?></a>
</div> <!-- /container -->

    <?php include("../javascript.php"); ?>

</body>
</html>