<?php
if (!isset($_SESSION)) {
	session_start();
}
require_once("init.php");
?>
<?php
	//para indicar con CSS dónde estamos
	$x = (explode('/', $_SERVER['PHP_SELF']));
	array_pop ($x);
	$estado_menu = array_pop ($x);
	if (($estado_menu!="configuracion") && ($estado_menu!="comunicacion") && ($estado_menu!="monitorizacion") && ($estado_menu!="info") && ($estado_menu!="cgi-bin") && ($estado_menu!="about") && ($estado_menu!="contact") ) {
		$estado_menu="home";
	}
?>
    <style type="text/css">
      body {
        padding-top: 60px; /* 60px to make the container go all the way to the bottom of the topbar */
      }
    </style>
    <div class="navbar navbar-fixed-top">
      <div class="navbar-inner">
        <div class="container">

          <!-- .btn-navbar is used as the toggle for collapsed navbar content -->
          <a class="btn btn-navbar" data-toggle="collapse" data-target=".nav-collapse">
            <span class="icon-bar"></span>
            <span class="icon-bar"></span>
            <span class="icon-bar"></span>
          </a>

          <!-- Be sure to leave the brand out there if you want it shown -->
          <a class="brand" href="<?php echo ($estado_menu=="home")? '.' : '../'; ?>">WSN</a>

          <!-- Everything you want hidden at 940px or less, place within here -->
          <div class="nav-collapse">
            <ul class="nav">

             <li<?php echo ($estado_menu=="home")? ' class="active"' : ''; ?>><a href="<?php echo ($estado_menu=="home")? '.' : '../'; ?>"><?php echo( HOME_MESSAGE ); ?></a></li>

             <li class="dropdown<?php echo ($estado_menu=="configuracion")? ' active' : ''; ?>" id="menu1">
              <a class="dropdown-toggle" data-toggle="dropdown" href="#menu1">
               <?php echo( CONFIGURACION_MESSAGE ); ?>
               <b class="caret"></b>
              </a>
              <ul class="dropdown-menu">
               <li class="nav-header"><?php echo( MANUAL_MESSAGE ); ?></li>
               <li><a href="<?php echo __path(ENABLE_LOCAL_WEB); ?>configuracion/osinfo.php"><?php echo( DETECT_OS_MESSAGE ); ?></a></li>
               <li><a href="<?php echo __path(ENABLE_LOCAL_WEB); ?>configuracion/detectar_port.php"><?php echo( DETECT_PORT_MESSAGE ); ?></a></li>
               <li><a href="<?php echo __path(ENABLE_LOCAL_WEB); ?>configuracion/configuracio.php"><?php echo( CONFIGURACION_MESSAGE ); ?></a></li>
               <li><a href="<?php echo __path(ENABLE_LOCAL_WEB); ?>configuracion/check_port.php"><?php echo( CHECK_PORT_MESSAGE ); ?></a></li>
               <li class="divider"></li>
               <li class="nav-header"><?php echo( AUTO_MESSAGE ); ?></li>
               <li><a href="<?php echo __path(ENABLE_LOCAL_WEB); ?>configuracion/detectar_tot.php"><?php echo( AUTODETECALL_MESSAGE ); ?></a></li>
              </ul>
             </li>

             <li class="dropdown<?php echo ($estado_menu=="comunicacion")? ' active' : ''; ?>" id="menu2">
              <a class="dropdown-toggle" data-toggle="dropdown" href="#menu2">
               <?php echo( COMUNICACION_MESSAGE ); ?>
               <b class="caret"></b>
              </a>
              <ul class="dropdown-menu">
               <li class="nav-header"><?php echo( READWRITE_MESSAGE ); ?></li>
               <li><a href="<?php echo __path(ENABLE_LOCAL_WEB); ?>comunicacion/setup_AP.php"><?php echo CONFIGURACION_MESSAGE; ?> AP</a></li>
               <li><a href="<?php echo __path(ENABLE_LOCAL_WEB); ?>comunicacion/python_ajax.php">AJAX Python</a></li>
               <li><a href="<?php echo __path(ENABLE_LOCAL_WEB); ?>comunicacion/led_mouse.php">AJAX <?php echo IMAGECONTROL_MSG; ?></a></li>
              </ul>
             </li>

             <li class="dropdown<?php echo ($estado_menu=="monitorizacion")? ' active' : ''; ?>" id="menu3">
              <a class="dropdown-toggle" data-toggle="dropdown" href="#menu3">
               <?php echo( MONITORIZATION_MESSAGE ); ?>
               <b class="caret"></b>
              </a>
             <ul class="dropdown-menu">
               <li class="nav-header"><?php echo( READ ); ?></li>
               <li><a href="<?php echo __path(ENABLE_LOCAL_WEB); ?>monitorizacion/graphpage_dynamic_AP.php"><?php echo( GRAPHAP_MSG ); ?></a></li>
               <li><a href="<?php echo __path(ENABLE_LOCAL_WEB); ?>monitorizacion/graphpage_dynamic_ED.php"><?php echo( GRAPHED_MSG ); ?></a></li>
             </ul>
            </li>

             <li class="dropdown<?php echo ($estado_menu=="info")? ' active' : ''; ?>" id="menu4">
              <a class="dropdown-toggle" data-toggle="dropdown" href="#menu4">
               <?php echo( INFORMATION_MESSAGE ); ?>
               <b class="caret"></b>
             </a>
             <ul class="dropdown-menu">
              <li><a href="<?php echo __path(ENABLE_LOCAL_WEB); ?>info/system.php"><?php echo( INFOOSALL_MESSAGE ); ?></a></li>
              <li><a href="<?php echo __path(ENABLE_LOCAL_WEB); ?>info/osinfo.php"><?php echo( INFOOS_MESSAGE ); ?></a></li>
              <li><a href="<?php echo __path(ENABLE_LOCAL_WEB); ?>info/apacheinfo.php"><?php echo( WEBSERVER_MSG ); ?></a></li>
              <li><a href="<?php echo __path(ENABLE_LOCAL_WEB); ?>info/mysqlinfo.php"><?php echo( MYSQLSERVER_MSG ); ?></a></li>
              <li><a href="<?php echo __path(ENABLE_LOCAL_WEB); ?>info/phpinfo_server.php"><?php echo( PHPSERVER_MSG ); ?></a></li>
              <li><a href="<?php echo __path(ENABLE_LOCAL_WEB); ?>info/phpinfo.php">PHP ALL info</a></li>
              <li><a href="<?php echo __path(ENABLE_LOCAL_WEB); ?>cgi-bin/test_cgi_python.php">Python test CGI</a></li>
              <li><a href="<?php echo __path(ENABLE_LOCAL_WEB); ?>cgi-bin/version.php">Python <?php echo VERSION_MESSAGE; ?></a></li>
             </ul>
            </li>

            <li<?php echo ($estado_menu=="about")? ' class="active"' : ''; ?>><a href="<?php echo __path(ENABLE_LOCAL_WEB); ?>about/"><?php echo( ABOUT_MESSAGE ); ?></a></li>

            <li<?php echo ($estado_menu=="contact")? ' class="active"' : ''; ?>><a href="<?php echo __path(ENABLE_LOCAL_WEB); ?>contact/"><?php echo( CONTACT_MESSAGE ); ?></a></li>

           </ul>
           <?php include(__path(ENABLE_LOCAL_WEB)."languages.php"); ?>
          </div><!--/.nav-collapse -->
        </div>
      </div>
    </div>
