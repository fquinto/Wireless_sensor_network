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
      document.enviar.adrED.focus()
      document.enviar.adrED.select()
      //lectura_serie()
    }

function getValueFromName(name)
{
  var radioButtons = document.getElementsByName(name);
  for (var x = 0; x < radioButtons.length; x ++)
  {
    if (radioButtons[x].checked)
    {
      return radioButtons[x].value;
    }
  }
}

    function lectura_serie(){
if (window.XMLHttpRequest)
  {// code for IE7+, Firefox, Chrome, Opera, Safari
  xmllectura=new XMLHttpRequest();
  }
else
  {// code for IE6, IE5
  xmllectura=new ActiveXObject("Microsoft.XMLHTTP");
  }
xmllectura.onreadystatechange=function()
  {
    document.getElementById("lectura_ajax").innerHTML=xmllectura.responseText;
  }

<?php if (isset($_SESSION['OS']) && $_SESSION['OS']!="")
{
 if ( $_SESSION['OS']=="LINUX" ) {
?>
xmllectura.open("GET","../cgi-bin/recibir_linux.py?puerto=<?php echo $_SESSION['puerto']; ?>&velocidad=<?php echo $_SESSION['velocidad']; ?>&databit=<?php echo $_SESSION['databit']; ?>&stopbit=<?php echo $_SESSION['stopbit']; ?>&paridad=<?php echo $_SESSION['paridad']; ?>&control=<?php echo $_SESSION['control']; ?>&veces="+document.enviar.veces.value,true);
<?php
 }
?>
<?php
 if ( $_SESSION['OS']=="WINDOWS" ) {
?>
xmllectura.open("GET","../cgi-bin/recibir_windows.py?puerto=<?php echo $_SESSION['puerto']; ?>&velocidad=<?php echo $_SESSION['velocidad']; ?>&databit=<?php echo $_SESSION['databit']; ?>&stopbit=<?php echo $_SESSION['stopbit']; ?>&paridad=<?php echo $_SESSION['paridad']; ?>&control=<?php echo $_SESSION['control']; ?>&veces="+document.enviar.veces.value,true);
<?php
 }
}
?>
xmllectura.send();
}

function escritura_serie(address,data)
{
if (data.length==0)
  {
  document.getElementById("escritura_ajax").innerHTML="";
  return;
  }
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
    document.getElementById("escritura_ajax").innerHTML=xmlhttp.responseText;
    }
  }
<?php if (isset($_SESSION['OS']) && $_SESSION['OS']!="")
{
 if ( $_SESSION['OS']=="LINUX" ) {
?>
xmlhttp.open("GET","../cgi-bin/enviar_linux.py?puerto=<?php echo $_SESSION['puerto']; ?>&velocidad=<?php echo $_SESSION['velocidad']; ?>&databit=<?php echo $_SESSION['databit']; ?>&stopbit=<?php echo $_SESSION['stopbit']; ?>&paridad=<?php echo $_SESSION['paridad']; ?>&control=<?php echo $_SESSION['control']; ?>&destino_msg=AP&rw=W&address="+address+"&data="+data,true);
<?php
 }
?>
<?php
 if ( $_SESSION['OS']=="WINDOWS" ) {
?>
xmlhttp.open("GET","../cgi-bin/enviar_windows.py?puerto=<?php echo $_SESSION['puerto']; ?>&velocidad=<?php echo $_SESSION['velocidad']; ?>&databit=<?php echo $_SESSION['databit']; ?>&stopbit=<?php echo $_SESSION['stopbit']; ?>&paridad=<?php echo $_SESSION['paridad']; ?>&control=<?php echo $_SESSION['control']; ?>&destino_msg=AP&rw=W&address="+address+"&data="+data,true);
<?php
 } ?>
  if (address=='61')
  {
    $.ajax({
      url: 'guarda.php?APaddress='+data
      });
  }
  if (address=='60')
  {
    $.ajax({
      url: 'guarda.php?EDaddress='+data
      });
  }
<?php
}
?>
xmlhttp.send();
}

function limpia_serie(){
  document.getElementById("escritura_ajax").innerHTML="";
}
</script>
</head>
<body>
<?php include("../menu.php"); ?>
<div class="container">
   <h1><?php echo( READWRITE_MESSAGE ); ?> <small><?php echo CONFIGURACION_MESSAGE; ?> AP</small></h1>
<?php if ( isset($_SESSION['velocidad']) && $_SESSION['velocidad']!="" && isset($_SESSION['puerto']) && $_SESSION['puerto']!="" && isset($_SESSION['OS']) && $_SESSION['OS']!="" && (writable_port($_SESSION['puerto'])==1) )
{
?>
 <div class="row">
  <div class="span7">
   <h2>Control <small><?php echo INFOOS_MESSAGE; ?>:<strong> <?php echo $_SESSION['OS'];?></strong> · <?php echo PORT_SELECTED_MESSAGE; ?> <strong><?php echo $_SESSION['puerto'];?></strong></small></h2>

    <form id="enviar" name="enviar" method="post" action="" class="form-horizontal">
      <fielset>
	  
	  <div class="form-actions">
      <button type="button" class="btn btn-small" onclick="limpia_serie()">
       <i class="icon-refresh"></i> <?php echo CLEAN; ?>
      </button>
      </div>

       <label class="control-label">1.- <?php echo ADDRESS_MESSAGE . " ED:"; ?></label>
       <div class="controls">
        <input name="adrED" type="text" id="adrED" size="10" maxlength="3" class="span1" value="<?php echo (isset($_SESSION['EDaddress']) && $_SESSION['EDaddress']!="") ? $_SESSION['EDaddress'] : "" ?>" />
        <button type="button" class="btn btn-small" onclick="escritura_serie('60',document.enviar.adrED.value)">
         <i class="icon-chevron-right"></i> <?php echo substr(SEND_BUTTON_MESSAGE, 0, -6) . " " . strtolower(ADDRESS_MESSAGE) . " ED"; ?>
        </button>
        </div>
        <br>
        <label class="control-label">2.- <?php echo ADDRESS_MESSAGE . " AP:"; ?></label>
       <div class="controls">
        <input name="adrAP" type="text" id="adrAP" size="10" maxlength="3" class="span1" value="<?php echo (isset($_SESSION['APaddress']) && $_SESSION['APaddress']!="") ? $_SESSION['APaddress'] : "" ?>" />
        <button type="button" class="btn btn-small" onclick="escritura_serie('61',document.enviar.adrAP.value)">
         <i class="icon-chevron-right"></i> <?php echo substr(SEND_BUTTON_MESSAGE, 0, -6) . " " . strtolower(ADDRESS_MESSAGE) . " AP"; ?>
        </button>
        </div>
        <br>
        <label class="control-label">3.- <?php echo "Control:"; ?></label>
       <div class="controls">
        <button type="button" class="btn btn-small" onclick="escritura_serie('62','001')">
         <i class="icon-cog"></i><?php echo CONFIGURACION_MESSAGE; ?> AP
        </button>
        </div>

      </fielset>
    </form>
  </div><!-- /span -->
  <div class="span5">
   <h2><?php echo CONSOLE_MESSAGE; ?></h2>
  <br>
   <span id="escritura_ajax"></span>
  </div><!-- /span -->
 </div><!-- /row -->
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