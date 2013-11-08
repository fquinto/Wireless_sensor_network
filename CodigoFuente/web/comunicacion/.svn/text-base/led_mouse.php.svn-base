<?php
if (!isset($_SESSION)) {
	session_start();
}
include("../init.php");
?><?php
writeheader(HOME_DESCRIP,KEYWORDS_MESSAGE);
?>
<script type="text/javascript">
function led(header,address,data)
{
if (window.XMLHttpRequest)
  {// code for IE7+, Firefox, Chrome, Opera, Safari
  xmlhttp=new XMLHttpRequest();
  }
else
  {// code for IE6, IE5
  xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
  }
<?php if (isset($_SESSION['OS']) && $_SESSION['OS']!="")
{
 if ( $_SESSION['OS']=="LINUX" ) {
?>
xmlhttp.open("GET","../cgi-bin/enviar_linux.py?puerto=<?php echo $_SESSION['puerto']; ?>&velocidad=<?php echo $_SESSION['velocidad']; ?>&databit=<?php echo $_SESSION['databit']; ?>&stopbit=<?php echo $_SESSION['stopbit']; ?>&paridad=<?php echo $_SESSION['paridad']; ?>&control=<?php echo $_SESSION['control']; ?>&destino_msg="+header+"&rw=W&address="+address+"&data="+data+"&lang=<?php echo (isset($_SESSION['lang'])) ? $_SESSION['lang'] : 'es'; ?>",true);
<?php
 }
?>
<?php
 if ( $_SESSION['OS']=="WINDOWS" ) {
?>
xmlhttp.open("GET","../cgi-bin/enviar_windows.py?puerto=<?php echo $_SESSION['puerto']; ?>&velocidad=<?php echo $_SESSION['velocidad']; ?>&databit=<?php echo $_SESSION['databit']; ?>&stopbit=<?php echo $_SESSION['stopbit']; ?>&paridad=<?php echo $_SESSION['paridad']; ?>&control=<?php echo $_SESSION['control']; ?>&destino_msg="+header+"&rw=W&address="+address+"&data="+data+"&lang=<?php echo (isset($_SESSION['lang'])) ? $_SESSION['lang'] : 'es'; ?>",true);
<?php
 }
}
?>
xmlhttp.send();
}
</script>
</head>
<body>
<?php include("../menu.php"); ?>
<div class="container">
   <h1><?php echo( READWRITE_MESSAGE ); ?> <small>AJAX <?php echo IMAGECONTROL_MSG; ?></small></h1>
<?php if ( isset($_SESSION['velocidad']) && $_SESSION['velocidad']!="" && isset($_SESSION['puerto']) && $_SESSION['puerto']!="" && isset($_SESSION['OS']) && $_SESSION['OS']!="" && (writable_port($_SESSION['puerto'])==1) )
{ ?>
  <div class="span7">
   <h2>Control <small><?php echo INFOOS_MESSAGE; ?>:<strong> <?php echo $_SESSION['OS'];?></strong> · <?php echo PORT_SELECTED_MESSAGE; ?> <strong><?php echo $_SESSION['puerto'];?></strong></small></h2>
    <br><br>
    <img src="../imagen/led.png" alt="led image" width="400" height="200" border="0" usemap="#led">
    <map name="led">
      <area shape="circle" alt="AP LED1 ON" href="#" coords="50,50,50" onmouseover="led('AP','11','000')"/>
      <area shape="circle" alt="AP LED2 ON" href="#" coords="150,50,50" onmouseover="led('AP','10','000')"/>
      <area shape="circle" alt="ED LED1 ON" href="#" coords="250,50,50" onmouseover="led('ED','11','000')"/>
      <area shape="circle" alt="ED LED2 ON" href="#" coords="350,50,50" onmouseover="led('ED','10','000')"/>
      <area shape="circle" alt="AP LED1 OFF" href="#" coords="50,150,50" onmouseover="led('AP','11','001')"/>
      <area shape="circle" alt="AP LED2 OFF" href="#" coords="150,150,50" onmouseover="led('AP','10','001')"/>
      <area shape="circle" alt="ED LED1 OFF" href="#" coords="250,150,50" onmouseover="led('ED','11','001')"/>
      <area shape="circle" alt="ED LED2 OFF" href="#" coords="350,150,50" onmouseover="led('ED','10','001')"/>
    </map>
  </div><!-- /span -->
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
     <?php } elseif (!isset($_SESSION['velocidad']) || $_SESSION['velocidad']=="") { ?>
       <a class="btn btn-primary" href="../configuracion/configuracio.php"><?php echo( CONFIG_PORT_MESSAGE );?></a>
     <?php } elseif (writable_port($_SESSION['puerto'])==0) { ?>
       <?php echo( CHECKNOK_MESSAGE );?>
       <br><br>
       <a class="btn btn-info" href="../configuracion/check_port.php"><i class="icon-pencil icon-white"></i> <?php echo( CHECK_MESSAGE );?></a>
     <?php } ?>
   </p>
 </div>
 <a class="btn" href="javascript:history.back(1)"><i class="icon-chevron-left"></i> <?php echo( GOBACK_MESSAGE );?></a>
 <a class="btn" href="../"><i class="icon-home"></i> <?php echo( GOHOME_MESSAGE );?></a>
<?php } ?>
</div> <!-- /container -->

    <?php include("../javascript.php"); ?>

</body>
</html>