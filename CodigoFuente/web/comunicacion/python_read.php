<?php
if (!isset($_SESSION)) {
	session_start();
}
include("../init.php");
?><?php
writeheader(HOME_DESCRIP,KEYWORDS_MESSAGE);
?>
<script>
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
function limpia_serie(){
  document.getElementById("lectura_ajax").innerHTML="";
}
</script>
</head>
<body onload="lectura_serie();">
<?php include("../menu.php"); ?>
<div class="container">
<h1>Python <small><?php echo( READ ); ?></small></h1>
<?php if (isset($_SESSION['puerto']) && $_SESSION['puerto']!="" && isset($_SESSION['OS']) && $_SESSION['OS']!="")
{ ?>
  <?php echo INFOOS_MESSAGE; ?> <strong><?php echo $_SESSION['OS'];?></strong><br>
  <?php echo PORT_SELECTED_MESSAGE; ?> <strong><?php echo $_SESSION['puerto'];?></strong>
  <br>

  <button type="button" class="btn btn-small" onclick="lectura_serie()">
    <i class="icon-play"></i> Play
  </button>
  <button type="button" class="btn btn-small" onclick="limpia_serie()">
    <i class="icon-refresh"></i> <?php echo CLEAN; ?>
  </button>

  <br>
  <span id="lectura_ajax"></span>
<?php
} else {
	echo ERROR_BEFOREWRITE_MESSAGE;
} ?>
</div>

    <?php include("../javascript.php"); ?>

</body>
</html>