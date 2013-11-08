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
<h1>PHP ALL info</h1><br>
<iframe src="phpinfo_all.php" width="960" height="390"></iframe>
</div>

    <?php include("../javascript.php"); ?>

</body>
</html>
