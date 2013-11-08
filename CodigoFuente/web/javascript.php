<?php
if (!isset($_SESSION)) {
	session_start();
}
?>
    <!-- Le javascript
    ================================================== -->
    <!-- Placed at the end of the document so the pages load faster -->
    <script src="<?php echo __path(ENABLE_LOCAL_WEB); ?>js/jquery.js"></script>
    <script src="<?php echo __path(ENABLE_LOCAL_WEB); ?>js/bootstrap.min.js"></script>
    <script src="<?php echo __path(ENABLE_LOCAL_WEB); ?>js/application.js"></script>