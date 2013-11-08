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
<h1><?php echo ABOUT_MESSAGE; ?> <small><?php echo( INFORMATION_MESSAGE ); ?></small></h1>
<br>
<?php echo ABOUT_TEXT; ?><br><br><br>
<img class="thumbnail" src="../imagen/LogoETSETB.png" alt="logo ETSETB UPC">

    <?php include("../footer.php"); ?>
</div>
    <?php include("../javascript.php"); ?>

</body>
</html>