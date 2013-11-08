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
      document.enviar.q2.focus()
      document.enviar.q2.select()
    }
</script>
<script type="text/javascript">
function escritura_serie(str)
{
if (str.length==0)
  {
  document.getElementById("txtHint").innerHTML="";
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
    document.getElementById("txtHint").innerHTML=xmlhttp.responseText;
    }
  }
<?php if (isset($_SESSION['OS']) && $_SESSION['OS']!="")
{
 if ( $_SESSION['OS']=="LINUX" ) {
?>
xmlhttp.open("GET","../cgi-bin/enviar_linux.py?q2="+str+"&puerto=<?php echo $_SESSION['puerto']; ?>&velocidad=<?php echo $_SESSION['velocidad']; ?>&databit=<?php echo $_SESSION['databit']; ?>&stopbit=<?php echo $_SESSION['stopbit']; ?>&paridad=<?php echo $_SESSION['paridad']; ?>&control=<?php echo $_SESSION['control']; ?>&destino_msg=FG&cmd=undefined",true);
<?php
 } else {
?>
xmlhttp.open("GET","../cgi-bin/enviar_windows.py?q2="+str+"&puerto=<?php echo $_SESSION['puerto']; ?>&velocidad=<?php echo $_SESSION['velocidad']; ?>&databit=<?php echo $_SESSION['databit']; ?>&stopbit=<?php echo $_SESSION['stopbit']; ?>&paridad=<?php echo $_SESSION['paridad']; ?>&control=<?php echo $_SESSION['control']; ?>&destino_msg=FG&cmd=undefined",true);
<?php
 }
}
?>
xmlhttp.send();
document.enviar.q2.value="";
}
</script>
</head>
<body onload="foco();">
<?php include("../menu.php"); ?>
<div class="container">
<?php if (isset($_SESSION['puerto']) && $_SESSION['puerto']!="" && isset($_SESSION['OS']) && $_SESSION['OS']!="")
{ ?>
    <?php echo INFOOS_MESSAGE; ?> <strong><?php echo $_SESSION['OS'];?></strong><br>
    <?php echo PORT_SELECTED_MESSAGE; ?> <strong><?php echo $_SESSION['puerto'];?></strong><br>
	<br><br>
	<form id="enviar" name="enviar" method="post" action="">
		<?php echo WRITE_MESSAGE; ?> <input name="q2" type="text" id="q2" size="10" maxlength="10" onkeyup="escritura_serie(this.value)" />
	</form><br>
	<span id="txtHint"></span>
<?php
} else {
	echo ERROR_BEFOREWRITE_MESSAGE;
} ?>
</div>

    <?php include("../javascript.php"); ?>

</body>
</html>