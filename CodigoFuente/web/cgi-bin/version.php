<?php
if (!isset($_SESSION)) {
	session_start();
}
include("../init.php");
?><?php
writeheader(HOME_DESCRIP,KEYWORDS_MESSAGE);
?>
</head>
<body>
<?php include("../menu.php"); ?>
<div class="container">
<?php if (isset($_SESSION['OS']) && $_SESSION['OS']=="LINUX")
{ ?>
	<iframe src="version_linux.py" width="960" height="400"></iframe>
<?php } ?>
<?php if (isset($_SESSION['OS']) && $_SESSION['OS']=="WINDOWS")
{ ?>
	<iframe src="version_windows.py" width="960" height="400"></iframe>
<?php } ?>
<?php if (isset($_SESSION['OS']) && $_SESSION['OS']!="LINUX" && $_SESSION['OS']!="WINDOWS")
{ 
	echo "ERROR: MAC?";
}
?>
<?php if (!isset($_SESSION['OS']))
{ 
	echo ERROR_OSNOT_DETECTED_MESSAGE2;
}
?>
</div>

    <?php include("../javascript.php"); ?>

</body>
</html>