<?php
if (!isset($_SESSION)) {
	session_start();
}
include("../init.php");
?>
<?php

$puerto = $_GET['q'];

if ( isset($_SESSION['OS']) && $_SESSION['OS']!="" && isset($_SESSION['puerto']) && $_SESSION['puerto']!="" && isset($_SESSION['velocidad']) && $_SESSION['velocidad']!="" && isset($_SESSION['databit']) && isset($_SESSION['paridad']) && isset($_SESSION['stopbit']) && isset($_SESSION['control']) )
{ ?>
<?php if ( writable_port($puerto)==1 ) { ?>
    <div class="alert alert-success">
    <a class="close" data-dismiss="alert" href="#">×</a>
    <?php echo CHECKOK_MESSAGE; ?>
    </div>
<?php } else {?>
    <div class="alert alert-error">
    <a class="close" data-dismiss="alert" href="#">×</a>
    <?php echo CHECKNOK_MESSAGE; ?> <a class="btn btn-mini" href="check_port.php"><?php echo INFORMATION_MESSAGE; ?></a></div>
<?php } ?>
<?php } ?>