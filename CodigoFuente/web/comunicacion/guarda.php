<?php
if (!isset($_SESSION)) {
	session_start();
}
if (isset($_GET['APaddress']) && $_GET['APaddress']!="")
{
  $_SESSION['APaddress']=$_GET['APaddress'];
}
if (isset($_GET['EDaddress']) && $_GET['EDaddress']!="")
{
  $_SESSION['EDaddress']=$_GET['EDaddress'];
}
?>