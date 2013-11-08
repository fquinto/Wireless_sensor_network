<?php
if (!isset($_SESSION)) {
	session_start();
}
include("../init.php");
?><?php
writeheader(HOME_DESCRIP,KEYWORDS_MESSAGE);
?>
<script>
    function lecturaserie(){
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
    document.getElementById("lectura").innerHTML=xmllectura.responseText;
  }

<?php if (isset($_SESSION['OS']) && $_SESSION['OS']!="")
{
 if ( $_SESSION['OS']=="LINUX" ) {
?>
xmllectura.open("GET","../cgi-bin/recibir_linux.py?puerto=<?php echo $_SESSION['puerto']; ?>&velocidad=<?php echo $_SESSION['velocidad']; ?>&databit=<?php echo $_SESSION['databit']; ?>&stopbit=<?php echo $_SESSION['stopbit']; ?>&paridad=<?php echo $_SESSION['paridad']; ?>&control=<?php echo $_SESSION['control']; ?>",true);
<?php
 } else {
?>
xmllectura.open("GET","../cgi-bin/recibir_windows.py?puerto=<?php echo $_SESSION['puerto']; ?>&velocidad=<?php echo $_SESSION['velocidad']; ?>&databit=<?php echo $_SESSION['databit']; ?>&stopbit=<?php echo $_SESSION['stopbit']; ?>&paridad=<?php echo $_SESSION['paridad']; ?>&control=<?php echo $_SESSION['control']; ?>",true);
<?php
 }
}
?>
xmllectura.send();
}
</script>
</head>
<body onload="lecturaserie();">
<?php include("../menu.php"); ?>
<div class="container">
<div class="row">
<div class="span8">
<h1>Lectura Python</h1><br>
<h2>Consola</h2>
<?php if (isset($_SESSION['puerto']) && $_SESSION['puerto']!="" && isset($_SESSION['OS']) && $_SESSION['OS']!="")
{ ?>
    <?php echo INFOOS_MESSAGE; ?> <strong><?php echo $_SESSION['OS'];?></strong><br>
    <?php echo PORT_SELECTED_MESSAGE; ?> <strong><?php echo $_SESSION['puerto'];?></strong><br>
	<br>
	<span id="lectura"></span>
<?php
} else {
	echo ERROR_BEFOREWRITE_MESSAGE;
} ?>
</div>
<div class="span8">
<h3>Nodos</h3><br>
<img src="nodos_image.php" title="nodos image" alt="nodos image" border="0" />
</div>
</div>
</div>

    <?php include("../javascript.php"); ?>

</body>
</html>