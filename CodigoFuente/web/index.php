<?php
if (!isset($_SESSION)) {
	session_start();
}
include("init.php");
?><?php
writeheader(HOME_DESCRIP,KEYWORDS_MESSAGE);
?>
<script>
function config_ajax(query)
{
  var xmlhttp;
  if (window.XMLHttpRequest)
    {// code for IE7+, Firefox, Chrome, Opera, Safari
    xmlhttp=new XMLHttpRequest();
    }
  else
    {// code for IE6, IE5
    xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
    }
  xmlhttp.onreadystatechange=function()
    {
    if (xmlhttp.readyState==4 && xmlhttp.status==200)
      {
      document.getElementById("myConfig").innerHTML=xmlhttp.responseText;
      }
    }
  xmlhttp.open("GET","configuracion/config_ajax.php?q="+query,true);
  xmlhttp.send();
}
function check_port(query)
{
  var xmlhttp;
  if (window.XMLHttpRequest)
    {// code for IE7+, Firefox, Chrome, Opera, Safari
    xmlhttp=new XMLHttpRequest();
    }
  else
    {// code for IE6, IE5
    xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
    }
  xmlhttp.onreadystatechange=function()
    {
    if (xmlhttp.readyState==4 && xmlhttp.status==200)
      {
      document.getElementById("infoCheckPort").innerHTML=xmlhttp.responseText;
      }
    }
  xmlhttp.open("GET","configuracion/check_port_ajax.php?q="+query,true);
  xmlhttp.send();
}
</script>
  </head>
  <body>
    <style>
    /*
    #svg {
        width: 500px;

    }
    */
    .row-fluid .span6 {
      width: 40.93617%;
    }
    svg {
      position: relative;
      width: 541px;
      height: 376px;
      left: 4px;
      top: 61px;
    }
    </style>
    <?php include("menu.php"); ?>
    <div class="container">
     <div class="row-fluid">
      <!-- Main hero unit for a primary marketing message or call to action -->
      <div class="hero-unit">
        <div class="row">
          <div class="span6">
           <h1><?php echo( WELCOME_MESSAGE ); ?></h1>
           <p><?php echo( INTRO_MESSAGE ); ?></p>
            <div id="myConfig">
<?php
if ( !isset($_SESSION['OS']) )
{ ?>
           <h2><?php echo( INFOOS_QUESTION ); ?></h2><p><a class="btn btn-primary btn-large" href="javascript:config_ajax('os');" title="<?php echo DETECT_OS_MESSAGE;?>"><?php echo( DETECT_OS_MESSAGE );?> &raquo;</a></p>
<?php
} else {
?>         <h2><?php echo( CONFIGURACION_MESSAGE ); ?>:</h2><p>
           <a class="btn btn-large btn-primary disabled" href="#"><?php echo $_SESSION['OS']; ?></a>
<?php
if ( isset($_SESSION['puerto']) && isset($_SESSION['OS']) )
{ ?>
           <a class="btn btn-large btn-primary disabled" href="#"><?php echo $_SESSION['puerto']; ?></a>
<?php
} elseif ( isset($_SESSION['OS']) ) { ?>
           <a class="btn btn-primary btn-large" href="javascript:config_ajax('port');" title="<?php echo "Auto ".strtolower( DETECT_PORT_MESSAGE );?>"><?php echo "Auto ".strtolower( DETECT_PORT_MESSAGE );?> &raquo;</a>
<?php } ?>
<?php if ( isset($_SESSION['velocidad']) && isset($_SESSION['puerto']) && isset($_SESSION['OS']) && isset($_SESSION['databit']) && isset($_SESSION['paridad']) && isset($_SESSION['stopbit']) && isset($_SESSION['control']) )
{ ?>
           <a class="btn btn-large btn-primary disabled" href="#"><?php echo $_SESSION['velocidad'] . " " . $_SESSION['databit'] . " " . $_SESSION['paridad'] . " " . $_SESSION['stopbit'] . " " . $_SESSION['control']; ?></a>
<?php
} elseif ( isset($_SESSION['puerto']) && isset($_SESSION['OS']) ) { ?>
           <a class="btn btn-primary btn-large" href="javascript:config_ajax('velocidad');" title="<?php echo "Auto ".strtolower( CONFIG_PORT_MESSAGE );?>"><?php echo "Auto ".strtolower( CONFIG_PORT_MESSAGE );?> &raquo;</a>
<?php }
}
?>
<?php
if ( isset($_SESSION['OS']) && (isset($_SESSION['puerto']) && isset($_SESSION['velocidad'])) )
{ ?>
           <a class="btn btn-info btn-large" href="javascript:check_port2('<?php echo $_SESSION['puerto']; ?>');" title="<?php echo CHECK_PORT_MESSAGE;?>"><i class="icon-pencil icon-white"></i> <?php echo( CHECK_MESSAGE );?></a>
<?php
}
?>
<?php
if ( isset($_SESSION['OS']) )
{ ?>
           </p>
           <p>
            <a class="btn" href="configuracion/configuracio.php" title="<?php echo ( MANUAL_MESSAGE );?>"><?php echo ( MANUAL_MESSAGE );?></a>
            <a class="btn btn-danger" href="configuracion/quita.php" title="<?php echo DELETE_MESSAGE . " " . strtolower(CONFIGURACION_MESSAGE); ?>"><i class="icon-trash icon-white"></i> <?php echo DELETE_MESSAGE;?></a>
           </p>
<?php
}
?>         </div>
          <div id="infoCheckPort">
          </div>
          </div> <!-- /span6 -->
           <div class="span6">
            <div id="svg">
<?php
// get contents of a image file (SVG) into a string
$filename = "imagen/portada_web.svg";
$handle = fopen($filename, "r");

// eliminar 114 bytes iniciales
fseek($handle, 114);

$contents = fread($handle, filesize($filename));
fclose($handle);
echo $contents;
?>
            </div> <!-- /svg -->
           </div> <!-- /span6 -->
        </div> <!-- /row -->
      </div> <!-- /hero-unit -->
    </div> <!-- /row-fluid -->
    </div> <!-- /container -->

    <?php include("javascript.php"); ?>
<script type="text/javascript" charset="utf-8">
function check_port2(query)
{
	$.ajaxSetup ({
		cache: false
	});

	var jsonUrl = "cgi-bin/check_port_<?php echo strtolower(giveme_os()); ?>.py?port="+query;
	$.getJSON(
		jsonUrl,
		function(json) {
			if (json==1) {
				var result = '<div class="alert alert-success"><a class="close" data-dismiss="alert" href="#">×</a><strong><?php echo OK_MESSAGE; ?></strong> <?php echo CHECKOK_MESSAGE; ?></div>';
			} else {
				var result = '<div class="alert alert-error"><a class="close" data-dismiss="alert" href="#">×</a><?php echo CHECKNOK_MESSAGE; ?> <a class="btn btn-mini" href="configuracion/check_port.php"><?php echo INFORMATION_MESSAGE; ?></a></div>';
			}
			$("#infoCheckPort").html(result);
		}
	);
}
</script>
  </body>
</html>