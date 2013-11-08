<?php
if (!isset($_SESSION)) {
	session_start();
}
include("../init.php");
?>
<?php
if ($_GET['q']=="os" ) {

// init clear all session's
$_SESSION['puerto'] = NULL;
unset($_SESSION['puerto']);
$_SESSION['velocidad'] = NULL;
$_SESSION['databit'] = NULL;
$_SESSION['paridad'] = NULL;
$_SESSION['stopbit'] = NULL;
$_SESSION['control'] = NULL;
unset($_SESSION['velocidad']);
unset($_SESSION['databit']);
unset($_SESSION['paridad']);
unset($_SESSION['stopbit']);
unset($_SESSION['control']);

$_SESSION['OS']=giveme_os();
?>
  <h2><?php echo( CONFIGURACION_MESSAGE ); ?>:</h2>
  <p>
  <a class="btn btn-large btn-primary disabled" href="#"><?php echo $_SESSION['OS']; ?></a>
<?php
if (isset($_SESSION['puerto']))
{ ?>
           <a class="btn btn-large btn-primary disabled" href="#"><?php echo $_SESSION['puerto']; ?></a>
<?php
} else { ?>
           <a class="btn btn-primary btn-large" href="javascript:config_ajax('port');" title="<?php echo "Auto ".strtolower( DETECT_PORT_MESSAGE );?>"><?php echo "Auto ".strtolower( DETECT_PORT_MESSAGE );?> &raquo;</a>
<?php } ?>
  </p>
<?php } ?>
<?php
if ($_GET['q']=="port") {

// init clear all session's
$_SESSION['velocidad'] = NULL;
$_SESSION['databit'] = NULL;
$_SESSION['paridad'] = NULL;
$_SESSION['stopbit'] = NULL;
$_SESSION['control'] = NULL;
unset($_SESSION['velocidad']);
unset($_SESSION['databit']);
unset($_SESSION['paridad']);
unset($_SESSION['stopbit']);
unset($_SESSION['control']);

if ( !(isset($_SESSION['OS'])) || $_SESSION['OS']=="" )
{
    $_SESSION['OS']=giveme_os();
}
if ( isset($_SESSION['OS']) && $_SESSION['OS']!="" )
{
    $_SESSION['puerto'] = giveme_port($_SESSION['OS']);
}
?>
  <h2><?php echo( CONFIGURACION_MESSAGE ); ?>:</h2>
  <p>
  <a class="btn btn-large btn-primary disabled" href="#"><?php echo $_SESSION['OS']; ?></a>
  <a class="btn btn-large btn-primary disabled" href="#"><?php echo $_SESSION['puerto']; ?></a>

<?php
if (isset($_SESSION['velocidad']))
{ ?>
           <a class="btn btn-large btn-primary disabled" href="#"><?php echo $_SESSION['velocidad'] . " " . $_SESSION['databit'] . " " . $_SESSION['paridad'] . " " . $_SESSION['stopbit'] . " " . $_SESSION['control']; ?></a>
<?php
} else { ?>
           <a class="btn btn-primary btn-large" href="javascript:config_ajax('velocidad');" title="<?php echo "Auto ".strtolower( CONFIG_PORT_MESSAGE );?>"><?php echo "Auto ".strtolower( CONFIG_PORT_MESSAGE );?> &raquo;</a>
<?php } ?>
</p>
<?php } ?>
<?php
if ($_GET['q']=="velocidad") {
if ( !(isset($_SESSION['OS'])) || $_SESSION['OS']=="" )
{
    $_SESSION['OS']=giveme_os();
}
if ( !(isset($_SESSION['puerto'])) || $_SESSION['puerto']=="" )
{
    $_SESSION['puerto'] = giveme_port($_SESSION['OS']);
}
if ( isset($_SESSION['OS']) && $_SESSION['OS']!="" && isset($_SESSION['puerto']) && $_SESSION['puerto']!="")
{
//configuració per defecte:
$_SESSION['velocidad']="9600";
$_SESSION['databit']="8";
$_SESSION['paridad']="none";
$_SESSION['stopbit']="1";
$_SESSION['control']="none";
}
?>
  <h2><?php echo( CONFIGURACION_MESSAGE ); ?>:</h2>
  <p>
  <a class="btn btn-large btn-primary disabled" href="#"><?php echo $_SESSION['OS']; ?></a>
  <a class="btn btn-large btn-primary disabled" href="#"><?php echo $_SESSION['puerto']; ?></a>
  <a class="btn btn-large btn-primary disabled" href="#"><?php echo $_SESSION['velocidad'] . " " . $_SESSION['databit'] . " " . $_SESSION['paridad'] . " " . $_SESSION['stopbit'] . " " . $_SESSION['control']; ?></a>
  <a class="btn btn-info btn-large" href="javascript:check_port2('<?php echo $_SESSION['puerto']; ?>');" title="<?php echo CHECK_PORT_MESSAGE;?>"><i class="icon-pencil icon-white"></i> <?php echo( CHECK_MESSAGE );?></a>
  </p>
<?php } ?>
<?php
if (isset($_SESSION['OS']) || isset($_SESSION['puerto']) || isset($_SESSION['velocidad']))
{ ?>
           <p>
             <a class="btn" href="configuracion/configuracio.php" title="<?php echo ( MANUAL_MESSAGE );?>"><?php echo ( MANUAL_MESSAGE );?></a>
             <a class="btn btn-danger" href="configuracion/quita.php" title="<?php echo DELETE_MESSAGE . " " . strtolower(CONFIGURACION_MESSAGE); ?>"><i class="icon-trash icon-white"></i> <?php echo DELETE_MESSAGE;?></a>
           </p>
<?php
}
?> 
