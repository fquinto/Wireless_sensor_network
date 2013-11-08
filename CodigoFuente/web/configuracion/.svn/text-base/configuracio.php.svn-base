<?php
if (!isset($_SESSION)) {
	session_start();
}
include("../init.php");
?><?php
writeheader(HOME_DESCRIP,KEYWORDS_MESSAGE);
/*
They need access to the /dev/ttyS0 serial port, which is owned by the dialout group.

I can chmod the permissions of the /dev/ttyS0 serial port every time the box reboots, but that's not a good solution. Is there any way to change the default group of /dev/ttyS0 to "users"? If not, is there a way to add the "users" group to "dialout"?

SOLVED I added
Code: KERNEL=="ttyS0", MODE="0777"
to /lib/udev/rules.d/10-local.rules and unplug & plug USB (or rebooted)


NOTE:
-jQquery fade out message from: "http://flintmaker.com/code/jquery-fade-message-in-or-out/"
*/
?>
<script type="text/javascript">
<!--
function messagebox(){
	$("#messageBox").removeClass().addClass("confirmbox").html("<?php echo SAVING_MESSAGE; ?>").fadeIn(2000).fadeOut(4000);
	setTimeout("document.forms['config'].submit();",3000);
}
-->
</script>
</head>
<body>
<?php include("../menu.php"); ?>
<div class="container">
<h1><?php echo( MANUAL_MESSAGE ); ?> <small><?php echo( CONFIGURACION_MESSAGE ); ?></small></h1>
<?php
$colname_puerto = "0";
if (isset($_POST['puerto']) && $_POST['puerto']!="") {
  $colname_puerto = (get_magic_quotes_gpc()) ? $_POST['puerto'] : addslashes($_POST['puerto']);
  $_SESSION['puerto']=$colname_puerto;
}
?>
<?php
if ( isset($_SESSION['OS']) && ($_SESSION['OS']!="") )
  {
    if ((!isset($_SESSION['puerto'])) && ($_SESSION['OS']=='WINDOWS'))
    {
?>
        <div class="span8">
	<form id='config' method="post" action="" class="form-horizontal">
        <fielset>

        <div class="control-group">
        <label class="control-label"><?php echo INFOOS_MESSAGE; ?>: </label>
        <input id="disabledInput" class="input-small disabled" type="text" disabled="" placeholder="<?php echo $_SESSION['OS'];?>">
        <a class="btn btn-danger" href="quita.php?quitar=os" title="<?php echo RESET_SELECTED_MESSAGE;?>"><i class="icon-trash icon-white"></i> <?php echo RESET_SELECTED_MESSAGE;?></a><br>
        </div>

	<div class="control-group">
        <label class="control-label"><?php echo PORT_SELECTED_MESSAGE; ?></label>
        <div class="controls">
	<select name="puerto" id="puerto" class="input-small span2" >
		<option value="COM1">COM 1</option>
		<option value="COM2">COM 2</option>
		<option value="COM3">COM 3</option>
		<option value="COM4">COM 4</option>
		<option value="COM5">COM 5</option>
		<option value="COM6">COM 6</option>
		<option value="COM7">COM 7</option>
		<option value="COM8">COM 8</option>
		<option value="COM9">COM 9</option>
		<option value="CNCA0">CNCA0</option>
		<option value="CNCB0">CNCB0</option>
		<option value="COM33">COM33</option>
		<option value="COM34">COM34</option>
		<option value="COM35">COM35</option>
	</select>
	<?php echo( DETECT_PORT_MESSAGE ); ?>: <select id="automanual" class="span2">
		<option value="0"><?php echo MANUAL_MESSAGE;?></option>
		<option value="1"><?php echo AUTO_MESSAGE;?></option>
	</select>
	</div>
        </div>
<?php
  }

  if ((!isset($_SESSION['puerto'])) && ($_SESSION['OS']=='LINUX'))
  {
?>
        <div class="span8">
        <form id='config' method="post" action="" class="form-horizontal">
        <fielset>

        <div class="control-group">
        <label class="control-label"><?php echo INFOOS_MESSAGE; ?>: </label>
        <input id="disabledInput" class="input-small disabled" type="text" disabled="" placeholder="<?php echo $_SESSION['OS'];?>">
        <a class="btn btn-danger" href="quita.php?quitar=os" title="<?php echo RESET_SELECTED_MESSAGE;?>"><i class="icon-trash icon-white"></i> <?php echo RESET_SELECTED_MESSAGE;?></a><br>
        </div>

	<div class="control-group">
        <label class="control-label"><?php echo PORT_SELECTED_MESSAGE; ?></label>
        <div class="controls">
	<select name="puerto" id="puerto" class="input-small span2" >
		<option value="/dev/ttyS0">/dev/ttyS0</option>
		<option value="/dev/ttyS1">/dev/ttyS1</option>
		<option value="/dev/ttyS2">/dev/ttyS2</option>
		<option value="/dev/ttyS3">/dev/ttyS3</option>
		<option value="/dev/ttyS30">/dev/ttyS30</option>
		<option value="/dev/ttyS31">/dev/ttyS31</option>
		<option value="/dev/ttyS32">/dev/ttyS32</option>
		<option value="/dev/ttyS33">/dev/ttyS33</option>
		<option value="/dev/ttyUSB0">/dev/ttyUSB0</option>
		<option value="/dev/ttyACM0">/dev/ttyACM0</option>
		<option value="/dev/ttyACM1">/dev/ttyACM1</option>
	</select>
	<?php echo( DETECT_PORT_MESSAGE ); ?>: <select id="automanual" class="span2">
		<option value="0"><?php echo MANUAL_MESSAGE;?></option>
		<option value="1"><?php echo AUTO_MESSAGE;?></option>
	</select>
	</div>
        </div>
<?php
  }

  if (isset($_SESSION['puerto']) && $_SESSION['puerto']!="" && isset($_SESSION['OS']) && $_SESSION['OS']!="")
  {
?>
    <div class="span8">
    <form id='config' method="post" action="accion.php?accion=configura" class="form-horizontal">
     <fielset>

        <div class="control-group">
        <label class="control-label"><?php echo INFOOS_MESSAGE; ?>: </label>
        <input id="disabledInput" class="input-small disabled" type="text" disabled="" placeholder="<?php echo $_SESSION['OS'];?>">
        <a class="btn btn-danger" href="quita.php?quitar=os" title="<?php echo RESET_SELECTED_MESSAGE;?>"><i class="icon-trash icon-white"></i> <?php echo RESET_SELECTED_MESSAGE;?></a><br>
        </div>

        <div class="control-group">
        <label class="control-label"><?php echo PORT_SELECTED_MESSAGE; ?></label>
        <input id="disabledInput" class="input-small disabled" type="text" disabled="" placeholder="<?php echo $_SESSION['puerto'];?>">
        <a class="btn" href="quita.php?quitar=puerto&ir=<?php echo substr($_SERVER['SCRIPT_NAME'],0,-4);?>" title="<?php echo CHANGE_PORT_MESSAGE; ?>"><i class="icon-wrench"></i> <?php echo CHANGE_PORT_MESSAGE; ?></a><br>
        </div>

      <div class="control-group">
       <label class="control-label"><?php echo( SPEED_MESSAGE ); ?></label>
        <div class="controls">
         <?php if ( isset($_SESSION['velocidad']) ) { ?>
         <select name="velocidad" id="velocidad" class="span2" >
          <option value="110" <?php echo (isset($_SESSION['velocidad']) && $_SESSION['velocidad']=="110") ? 'selected="selected" ' : ''; ?>>110</option>
          <option value="150" <?php echo (isset($_SESSION['velocidad']) && $_SESSION['velocidad']=="150") ? 'selected="selected" ' : ''; ?>>150</option>
          <option value="300" <?php echo (isset($_SESSION['velocidad']) && $_SESSION['velocidad']=="300") ? 'selected="selected" ' : ''; ?>>300</option>
          <option value="600" <?php echo (isset($_SESSION['velocidad']) && $_SESSION['velocidad']=="600") ? 'selected="selected" ' : ''; ?>>600</option>
          <option value="1200" <?php echo (isset($_SESSION['velocidad']) && $_SESSION['velocidad']=="1200") ? 'selected="selected" ' : ''; ?>>1200</option>
          <option value="2400" <?php echo (isset($_SESSION['velocidad']) && $_SESSION['velocidad']=="2400") ? 'selected="selected" ' : ''; ?>>2400</option>
          <option value="4800" <?php echo (isset($_SESSION['velocidad']) && $_SESSION['velocidad']=="4800") ? 'selected="selected" ' : ''; ?>>4800</option>
          <option value="9600" <?php echo (isset($_SESSION['velocidad']) && $_SESSION['velocidad']=="9600") ? 'selected="selected" ' : ''; ?>>9600</option>
          <option value="38400" <?php echo (isset($_SESSION['velocidad']) && $_SESSION['velocidad']=="38400") ? 'selected="selected" ' : ''; ?>>38400</option>
          <option value="57600" <?php echo (isset($_SESSION['velocidad']) && $_SESSION['velocidad']=="57600") ? 'selected="selected" ' : ''; ?>>57600</option>
          <option value="115200" <?php echo (isset($_SESSION['velocidad']) && $_SESSION['velocidad']=="115200") ? 'selected="selected" ' : ''; ?>>115200</option>
         </select>
         <?php } else { ?>
         <select name="velocidad" id="velocidad" class="span2" >
          <option value="110" >110</option>
          <option value="150" >150</option>
          <option value="300" >300</option>
          <option value="600" >600</option>
          <option value="1200" >1200</option>
          <option value="2400" >2400</option>
          <option value="4800" >4800</option>
          <option value="9600" selected="selected" >9600</option>
          <option value="38400" >38400</option>
          <option value="57600" >57600</option>
          <option value="115200" >115200</option>
         </select>
         <?php } ?>
         <p class="help-inline"><?php echo DEFAULT_MESSAGE; ?> "9600"</p>
        </div>
      </div>

    <div class="control-group">
    <label class="control-label"><?php echo( DATABIT_MESSAGE ); ?></label>
     <div class="controls">
     <?php if ( isset($_SESSION['databit']) ) { ?>
     <select name="databit" id="databit" class="span1" >
		<option value="5" <?php echo (isset($_SESSION['databit']) && $_SESSION['databit']=="5") ? 'selected="selected" ' : ''; ?>>5</option>
		<option value="6" <?php echo (isset($_SESSION['databit']) && $_SESSION['databit']=="6") ? 'selected="selected" ' : ''; ?>>6</option>
		<option value="7" <?php echo (isset($_SESSION['databit']) && $_SESSION['databit']=="7") ? 'selected="selected" ' : ''; ?>>7</option>
		<option value="8" <?php echo (isset($_SESSION['databit']) && $_SESSION['databit']=="8") ? 'selected="selected" ' : ''; ?>>8</option>
    </select>
    <?php } else { ?>
     <select name="databit" id="databit" class="span1" >
		<option value="5" >5</option>
		<option value="6" >6</option>
		<option value="7" >7</option>
		<option value="8" selected="selected" >8</option>
    </select>
    <?php } ?>
    <p class="help-inline"><?php echo DEFAULT_MESSAGE; ?> "8"</p>
    </div>
    </div>

    <div class="control-group">
    <label class="control-label"><?php echo( PARITY_MESSAGE ); ?></label>
    <div class="controls">
    <select name="paridad" id="paridad" class="span2" >
		<option value="none" <?php echo (isset($_SESSION['paridad']) && $_SESSION['paridad']=="none") ? 'selected="selected" ' : ''; ?>><?php echo( NOPARITY_MESSAGE ); ?></option>
		<option value="odd" <?php echo (isset($_SESSION['paridad']) && $_SESSION['paridad']=="odd") ? 'selected="selected" ' : ''; ?>><?php echo( PARITYODD_MESSAGE ); ?></option>
		<option value="even" <?php echo (isset($_SESSION['paridad']) && $_SESSION['paridad']=="even") ? 'selected="selected" ' : ''; ?>><?php echo( PARITYEVEN_MESSAGE ); ?></option>
     </select> <p class="help-inline"><?php echo DEFAULT_MESSAGE . ' "' . NOPARITY_MESSAGE . '"'; ?></p>
     </div>
    </div>
<?php
/*
<select name="stopbit" id="stopbit" class="span1" >
	<option value="1" <?php echo (isset($_SESSION['stopbit']) && $_SESSION['stopbit']=="1") ? 'selected="selected" ' : ''; ?>>1</option>
	<option value="1.5" <?php echo (isset($_SESSION['stopbit']) && $_SESSION['stopbit']=="1.5") ? 'selected="selected" ' : ''; ?>>1.5</option>
	<option value="2.0" <?php echo (isset($_SESSION['stopbit']) && $_SESSION['stopbit']=="2.0") ? 'selected="selected" ' : ''; ?>>2.0</option>
</select>
*/
?>
    <div class="control-group">
    <label class="control-label"><?php echo( STOPBIT_MESSAGE ); ?></label>
    <div class="controls">
    <label class="radio inline">
    <?php if ( isset($_SESSION['stopbit']) ) { ?>
    <input id="optionsRadios1" type="radio" <?php echo (isset($_SESSION['stopbit']) && $_SESSION['stopbit']=="1") ? 'checked=""' : ''; ?> value="1" name="stopbit">
    1
    </label>
    <label class="radio inline">
    <input id="optionsRadios1.5" type="radio" <?php echo (isset($_SESSION['stopbit']) && $_SESSION['stopbit']=="1.5") ? 'checked=""' : ''; ?> value="1.5" name="stopbit">
    1.5
    </label>
    <label class="radio inline">
    <input id="optionsRadios2" type="radio" <?php echo (isset($_SESSION['stopbit']) && $_SESSION['stopbit']=="2.0") ? 'checked=""' : ''; ?> value="2" name="stopbit">
    2
    <?php } else { ?>
    <input id="optionsRadios1" type="radio" checked="" value="1" name="stopbit">
    1
    </label>
    <label class="radio inline">
    <input id="optionsRadios1.5" type="radio" value="1.5" name="stopbit">
    1.5
    </label>
    <label class="radio inline">
    <input id="optionsRadios2" type="radio" value="2" name="stopbit">
    2
    <?php } ?>
    </label>
    <p class="help-block"><?php echo DEFAULT_MESSAGE; ?> "1"</p>
    </div>
    </div>

    <div class="control-group">
     <label class="control-label"><?php echo( CONTROL_MESSAGE ); ?></label>
      <div class="controls">
       <select name="control" id="control" class="span2" >
		<option value="none" <?php echo (isset($_SESSION['control']) && $_SESSION['control']=="none") ? 'selected="selected" ' : ''; ?>><?php echo( NOCONTROL_MESSAGE ); ?></option>
		<option value="rts/cts" <?php echo (isset($_SESSION['control']) && $_SESSION['control']=="rts/cts") ? 'selected="selected" ' : ''; ?>>rts/cts (hardware)</option>
		<option value="xon/xoff" <?php echo (isset($_SESSION['control']) && $_SESSION['control']=="xon/xoff") ? 'selected="selected" ' : ''; ?>>xon/xoff (software)</option>
       </select> <p class="help-inline"><?php echo DEFAULT_MESSAGE . ' "' . NOCONTROL_MESSAGE . '"'; ?></p>
      </div>
    </div>

<?php
  }
?>
    <div class="form-actions">
     <a class="btn btn-primary" href="javascript:messagebox();" ><?php echo SAVE_MESSAGE;?></a>
     <a class="btn" href="javascript:history.back(1)"><i class="icon-chevron-left"></i> <?php echo( GOBACK_MESSAGE );?></a>
     <a class="btn" href="../"><i class="icon-home"></i> <?php echo( GOHOME_MESSAGE );?></a>
     <a class="btn btn-danger" href="quita.php" ><i class="icon-trash icon-white"></i> <?php echo DELETE_MESSAGE . " " . strtolower(CONFIGURACION_MESSAGE); ?></a>
     <div id="messageBox"> </div>
    </div>

   </fielset>
  </form>
  </div> <!-- /row -->
 </div> <!-- /span -->
<?php
  } else {
?>
    <div class="alert alert-block alert-error fade in">
      <button type="button" class="close" data-dismiss="alert">×</button>
      <h4 class="alert-heading">ERROR</h4>
      <p><?php echo ERROR_OSNOT_DETECTED_MESSAGE; ?></p>
      <p>
        <?php if (!isset($_SESSION['OS']) || $_SESSION['OS']=="") { ?>
          <a class="btn btn-primary" href="../configuracion/osinfo.php"><?php echo( DETECT_OS_MESSAGE );?></a>
        <?php } ?>
      </p>
  </div>
<a class="btn" href="javascript:history.back(1)"><i class="icon-chevron-left"></i> <?php echo( GOBACK_MESSAGE );?></a>
<a class="btn" href="../"><i class="icon-home"></i> <?php echo( GOHOME_MESSAGE );?></a>
<?php
  }
?>
</div> <!-- /container -->

    <?php include("../javascript.php"); ?>
<script type="text/javascript" charset="utf-8">
	$(function(){
		$("select#automanual").change(function(){
			<?php if ( $_SESSION['OS']=="LINUX" )
			        {
			?>
			$.getJSON("../cgi-bin/givemeports_linux.py",{id: $(this).val()}, function(j){
			<?php   } ?>
			<?php if ( $_SESSION['OS']=="WINDOWS" )
			        {
			?>
			$.getJSON("../cgi-bin/portsnobusy_windows.py",{id: $(this).val()}, function(j){
			<?php   } ?>
				var options = '';
				for (var i = 0; i < j.length; i++) {
					options += '<option value="' + j[i].optionValue + '">' + j[i].optionDisplay + '</option>';
				}
				$("#puerto").html(options);
				$('#puerto option:first').attr('selected', 'selected');
			})
		})			
	})
</script>
</body>
</html>