<?php
if (!isset($_SESSION)) {
	session_start();
}
include("../init.php");
?><?php
writeheader(HOME_DESCRIP,KEYWORDS_MESSAGE);
?>
<script type="text/javascript">

function changeColor(color) {
 var path=document.getElementById("system_image").getSVGDocument().getElementById("path4305");
 path.style.setProperty("fill",color, "");
 var path=document.getElementById("system_image").getSVGDocument().getElementById("path4309");
 path.style.setProperty("fill",color, "");

 document.getElementById("text4317").setAttribute("stroke", "red");
}

function changeMultipleColor(color) {
 var group=document.getElementById("system_image").getSVGDocument().getElementById("rect2997");
 var elements=group.getElementsByTagName("path");
 for (var i=0; i<elements.length; i++) {
  elements[i].style.setProperty("stroke", color, "");
 }
}

</script>
</head>
<body>
<?php include("../menu.php"); ?>
<div class="container">
<div class="row">
<div class="span8">
<h1><?php echo INFOOSALL_MESSAGE; ?> <small><?php echo DETECTED_MSG; ?></small></h1>
<br>
<form name="form1">

Color: <input type="text" name="color" value="#FFFF00" /> <br/>

<input type="button" value="Change color"
 onclick="javascript:changeColor(this.form.color.value);"/> <br/>
<input type="button" value="Change multiple elements"
 onclick="javascript:changeMultipleColor(this.form.color.value);"/> <br/>

</form>
<embed id="system_image" src="system_image_svg.php" width="915" height="256" />

</div>
</div>

    <?php include("../javascript.php"); ?>

</body>
</html>