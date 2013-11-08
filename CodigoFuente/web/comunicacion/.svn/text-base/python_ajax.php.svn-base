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
      document.enviar.data.focus()
      document.enviar.data.select()
      lectura_serie()
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

    function lectura_serie(veces){
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
xmllectura.open("GET","../cgi-bin/recibir_linux.py?puerto=<?php echo $_SESSION['puerto']; ?>&velocidad=<?php echo $_SESSION['velocidad']; ?>&databit=<?php echo $_SESSION['databit']; ?>&stopbit=<?php echo $_SESSION['stopbit']; ?>&paridad=<?php echo $_SESSION['paridad']; ?>&control=<?php echo $_SESSION['control']; ?>&veces="+veces+"&lang=<?php echo (isset($_SESSION['lang'])) ? $_SESSION['lang'] : 'es'; ?>",true);
<?php
 }
?>
<?php
 if ( $_SESSION['OS']=="WINDOWS" ) {
?>
xmllectura.open("GET","../cgi-bin/recibir_windows.py?puerto=<?php echo $_SESSION['puerto']; ?>&velocidad=<?php echo $_SESSION['velocidad']; ?>&databit=<?php echo $_SESSION['databit']; ?>&stopbit=<?php echo $_SESSION['stopbit']; ?>&paridad=<?php echo $_SESSION['paridad']; ?>&control=<?php echo $_SESSION['control']; ?>&veces="+veces+"&lang=<?php echo (isset($_SESSION['lang'])) ? $_SESSION['lang'] : 'es'; ?>",true);
<?php
 }
}
?>
xmllectura.send();
}

function sleep(millisegundos) {
  var inicio = new Date().getTime();
  while ((new Date().getTime() - inicio) < millisegundos){}
}

function escritura_serie(rw,address,data)
{
limpia_serie();
if (data.length==0)
  {
    limpia_serie();
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
xmlhttp.open("GET","../cgi-bin/com_linux.py?puerto=<?php echo $_SESSION['puerto']; ?>&velocidad=<?php echo $_SESSION['velocidad']; ?>&databit=<?php echo $_SESSION['databit']; ?>&stopbit=<?php echo $_SESSION['stopbit']; ?>&paridad=<?php echo $_SESSION['paridad']; ?>&control=<?php echo $_SESSION['control']; ?>&destino_msg="+getValueFromName("destino_msg")+"&rw="+rw+"&address="+address+"&data="+data+"&lang=<?php echo (isset($_SESSION['lang'])) ? $_SESSION['lang'] : 'es'; ?>",true);
<?php
 }
?>
<?php
 if ( $_SESSION['OS']=="WINDOWS" ) {
?>
xmlhttp.open("GET","../cgi-bin/com_windows.py?puerto=<?php echo $_SESSION['puerto']; ?>&velocidad=<?php echo $_SESSION['velocidad']; ?>&databit=<?php echo $_SESSION['databit']; ?>&stopbit=<?php echo $_SESSION['stopbit']; ?>&paridad=<?php echo $_SESSION['paridad']; ?>&control=<?php echo $_SESSION['control']; ?>&destino_msg="+getValueFromName("destino_msg")+"&rw="+rw+"&address="+address+"&data="+data+"&lang=<?php echo (isset($_SESSION['lang'])) ? $_SESSION['lang'] : 'es'; ?>",true);
<?php
 }
}
?>
xmlhttp.send();
document.enviar.data.value="";
document.enviar.data.focus();

}

function limpia_serie(){
  document.getElementById("escritura_ajax").innerHTML="";
  document.getElementById("lectura_ajax").innerHTML="";
}
</script>
</head>
<body>
<?php include("../menu.php"); ?>
<div class="container">
   <h1><?php echo( READWRITE_MESSAGE ); ?> <small>AJAX Python</small></h1>
<?php if ( isset($_SESSION['velocidad']) && $_SESSION['velocidad']!="" && isset($_SESSION['puerto']) && $_SESSION['puerto']!="" && isset($_SESSION['OS']) && $_SESSION['OS']!="" && (writable_port($_SESSION['puerto'])==1) )
{ ?>
  <div class="row">
  <div class="span7">
   <h2>Control <small><?php echo INFOOS_MESSAGE; ?>:<strong> <?php echo $_SESSION['OS'];?></strong> · <?php echo PORT_SELECTED_MESSAGE; ?> <strong><?php echo $_SESSION['puerto'];?></strong></small></h2>

    <form id="enviar" name="enviar" method="post" action="" class="form-horizontal">
      <fielset>
      
      <div class="form-actions"><h3><?php echo READ;?></h3>
       <?php echo TIMESREPEATER; ?>
       <input name="veces" type="text" id="veces" size="10" maxlength="15" class="span1" value="<?php echo ENDLESS; ?>" />
       <button type="button" class="btn btn-small" onclick="lectura_serie(document.enviar.veces.value)">
        <i class="icon-play"></i> Play
       </button>

      <button type="button" class="btn btn-small" onclick="limpia_serie()">
       <i class="icon-refresh"></i> <?php echo CLEAN; ?>
      </button>
    </div>

      <div class="control-group"><h3><?php echo WRITE;?></h3>

      <label class="control-label"><?php echo TARGET_MESSAGE . ":"; ?></label>
      <div class="controls">
      <label class="radio inline">
      <input id="optionsRadiosAP" type="radio" <?php echo (isset($_SESSION['destino_msg']) && $_SESSION['destino_msg']=="AP") ? 'checked=""' : ''; ?> value="AP" name="destino_msg">
      AP
      </label>
      <label class="radio inline">
      <input id="optionsRadiosED" type="radio" <?php echo (isset($_SESSION['destino_msg']) && $_SESSION['destino_msg']=="ED") ? 'checked=""' : ''; ?> value="ED" name="destino_msg">
      ED
      </label>
      <label class="radio inline">
      <input id="optionsRadiosFG" type="radio" <?php echo (isset($_SESSION['destino_msg']) && $_SESSION['destino_msg']=="FG") ? 'checked=""' : ''; ?> value="FG" name="destino_msg">
      FPGA
      </label>
      </div>
<br>
      <label class="control-label"><?php echo READWRITE_MESSAGE . ":"; ?></label>
      <div class="controls">
      <label class="radio inline">
      <input id="optionsRadiosREAD" type="radio" checked="" value="R" name="readwrite_msg">
      <?php echo READ;?>
      </label>
      <label class="radio inline">
      <input id="optionsRadiosWRITE" type="radio" value="W" name="readwrite_msg">
      <?php echo WRITE;?>
      </label>
      </div>
<br>
      <label class="control-label"><?php echo ADDRESS_MESSAGE . ":"; ?></label>
      <div class="controls">
      <input name="address" type="text" id="address" size="3" maxlength="2" class="span1" />
      <?php echo GRAPHIC_DATA . ":"; ?> <input name="data" type="text" id="data" size="4" maxlength="3" class="span1" /><br><br>
	<button type="button" class="btn btn-small" onclick="escritura_serie(getValueFromName('readwrite_msg'),document.enviar.address.value,document.enviar.data.value)">
	  <i class="icon-chevron-right"></i> <?php echo substr(SEND_BUTTON_MESSAGE, 0, -6); ?>
	</button>
       </div>
      
      <br>
	  <label class="control-label"><?php echo CONTROLS_MESSAGE . ":"; ?></label>
	  <div class="controls">
		<button type="button" class="btn btn-small" onclick="escritura_serie('R','50','000')">
		  <i class="icon-info-sign"></i> Temp
		</button>
		<button type="button" class="btn btn-small" onclick="escritura_serie('R','51','000')">
		  <i class="icon-info-sign"></i> RSSI
		</button>
		<button type="button" class="btn btn-small" onclick="escritura_serie('R','52','000')">
		  <i class="icon-info-sign"></i> Volt
		</button>
		<button type="button" class="btn btn-small btn-success" onclick="escritura_serie('W','11','000')">
		  <i class="icon-asterisk icon-white"></i> led1_on
		</button>
		<button type="button" class="btn btn-small" onclick="escritura_serie('W','11','001')">
		  <i class="icon-asterisk"></i> led1_off
		</button>
		<button type="button" class="btn btn-small btn-danger" onclick="escritura_serie('W','10','000')">
		  <i class="icon-asterisk icon-white"></i> led2_on
		</button>
		<button type="button" class="btn btn-small" onclick="escritura_serie('W','10','001')">
		  <i class="icon-asterisk"></i> led2_off
		</button>
	  </div>

       </div>

      </fielset>
    </form>
  </div><!-- /span -->
  <div class="span5">
   <h2><?php echo CONSOLE_MESSAGE; ?></h2>
  <br>
   <span id="escritura_ajax"></span>
   <span id="lectura_ajax"></span>
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