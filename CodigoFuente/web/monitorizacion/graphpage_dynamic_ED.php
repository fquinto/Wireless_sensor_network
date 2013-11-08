<?php
if (!isset($_SESSION)) {
	session_start();
}
include("../init.php");
?><?php
writeheader(HOME_DESCRIP,KEYWORDS_MESSAGE);
?>
<?php if ( isset($_SESSION['velocidad']) && $_SESSION['velocidad']!="" && isset($_SESSION['puerto']) && $_SESSION['puerto']!="" && isset($_SESSION['OS']) && $_SESSION['OS']!="" && (writable_port($_SESSION['puerto'])==1) )
{
?>
<script type='text/javascript' src='../js/jquery.js'></script>

<script type="text/javascript">
		var chart; // global
		
		/**
		 * Request data from the server, add it to the graph and set a timeout to request again
		 */
		function requestData() {
			$.ajax({
				
<?php if (isset($_SESSION['OS']) && $_SESSION['OS']=="LINUX")
{ ?>
				url: '../cgi-bin/recibir_linux_json.py?puerto=<?php echo $_SESSION['puerto']; ?>&velocidad=<?php echo $_SESSION['velocidad']; ?>&databit=<?php echo $_SESSION['databit']; ?>&stopbit=<?php echo $_SESSION['stopbit']; ?>&paridad=<?php echo $_SESSION['paridad']; ?>&control=<?php echo $_SESSION['control']; ?>&header=B',
<?php } ?>
<?php if (isset($_SESSION['OS']) && $_SESSION['OS']=="WINDOWS")
{ ?>
				url: '../cgi-bin/recibir_windows_json.py?puerto=<?php echo $_SESSION['puerto']; ?>&velocidad=<?php echo $_SESSION['velocidad']; ?>&databit=<?php echo $_SESSION['databit']; ?>&stopbit=<?php echo $_SESSION['stopbit']; ?>&paridad=<?php echo $_SESSION['paridad']; ?>&control=<?php echo $_SESSION['control']; ?>&header=B',
				/*url: 'json_data.php',*/
<?php } ?>
				success: function(point) {
					var series = chart.series[0],
					shift = series.data.length > 20; // shift if the series is longer than 20
					// add the point
					chart.series[0].addPoint(eval(point[0]), true, shift);

					var series = chart.series[1],
					shift = series.data.length > 20; // shift if the series is longer than 20
					// add the point
					chart.series[1].addPoint(eval(point[1]), true, shift);
					
					var series = chart.series[2],
					shift = series.data.length > 20; // shift if the series is longer than 20
					// add the point
					chart.series[2].addPoint(eval(point[2]), true, shift);
					
					// call it again after (1000 = one second)
					setTimeout(requestData, 1000);
				},
				cache: false
			});
		}
			
		$(document).ready(function() {
			chart = new Highcharts.Chart({
				credits: {
					enabled: false
				},
				chart: {
					renderTo: 'container',
					defaultSeriesType: 'spline',
					events: {
						load: requestData
					}
				},
				title: {
					text: 'Live data from ED'
				},
				xAxis: {
					type: 'datetime',
					tickPixelInterval: 150,
					maxZoom: 20 * 1000
				},
				yAxis: [{ // Primary yAxis
					labels: {
						formatter: function() {
							return this.value +'°C';
						},
						style: {
							color: '#4572A7'
						}
					},
					minPadding: 0.2,
					maxPadding: 0.2,
					title: {
						text: 'Temperature',
						style: {
							color: '#4572A7'
						}
					}
				}, { // Secondary yAxis
					minPadding: 0.2,
					maxPadding: 0.2,
					title: {
						text: 'Battery',
						style: {
							color: '#AA4643'
						}
					},
					labels: {
						formatter: function() {
							return this.value +' V';
						},
						style: {
							color: '#AA4643'
						}
					},
					opposite: true
				}, { // Tertiary yAxis
					gridLineWidth: 0,
					minPadding: 0.2,
					maxPadding: 0.2,
					title: {
						text: 'RSSI',
						style: {
							color: '#89A54E'
						}
					},
					labels: {
						formatter: function() {
							return this.value +' %';
						},
						style: {
							color: '#89A54E'
						}
					},
					opposite: true
				}],
				tooltip: {
					formatter: function() {
						var unit = {
							'Battery': 'V',
							'Temperature': '°C',
							'RSSI': '%'
						}[this.series.name];
		
						return ''+
							'<b>' + this.series.name + ' ' + this.y + ' ' + unit + '</b>' + '<br>@' + Highcharts.dateFormat('%H:%M:%S', this.x) + 'h';
					}
				},
				series: [{
					name: 'Temperature',
					data: []
				}, {
					name: 'Battery',
					color: '#AA4643',
					yAxis: 1,
					data: []
				}, {
					name: 'RSSI',
					color: '#89A54E',
					yAxis: 2,
					data: [],
					dashStyle: 'shortdot'
				}]
			});		
		});
</script>
<?php } ?>
</head>
<body>
<?php include("../menu.php"); ?>
<div class="container">
<h1><?php echo( READ ); ?> <small><?php echo( GRAPHED_MSG ); ?></small></h1>
<?php if ( isset($_SESSION['velocidad']) && $_SESSION['velocidad']!="" && isset($_SESSION['puerto']) && $_SESSION['puerto']!="" && isset($_SESSION['OS']) && $_SESSION['OS']!="" && (writable_port($_SESSION['puerto'])==1) )
{
?>
<script src="../js/highcharts.js"></script>
<script src="../js/exporting.js"></script>
<div id="container" style="min-width: 400px; height: 400px; margin: 0 auto"></div>
</div>
<?php
} else { ?>
 <div class="alert alert-block alert-error fade in">
   <button type="button" class="close" data-dismiss="alert">×</button>
   <h4 class="alert-heading">ERROR</h4>
   <p><?php echo ERROR_BEFOREWRITE_MESSAGE; ?></p>
   <p>
     <?php if (!isset($_SESSION['OS']) || $_SESSION['OS']=="") { ?>
       <a class="btn btn-primary" href="../configuracion/osinfo.php"><?php echo( DETECT_OS_MESSAGE );?></a>
     <?php } elseif (!isset($_SESSION['puerto']) || $_SESSION['puerto']=="") { ?>
       <a class="btn btn-primary" href="../configuracion/detectar_port.php"><?php echo( DETECT_PORT_MESSAGE );?></a>
     <?php } elseif (!isset($_SESSION['velocidad']) || $_SESSION['velocidad']=="") { ?>
       <a class="btn btn-primary" href="../configuracion/configuracio.php"><?php echo( CONFIG_PORT_MESSAGE );?></a>
     <?php } elseif (writable_port($_SESSION['puerto'])==0) { ?>
       <?php echo( CHECKNOK_MESSAGE );?>
       <br><br>
       <a class="btn btn-info" href="../configuracion/check_port.php"><i class="icon-pencil icon-white"></i> <?php echo( CHECK_MESSAGE );?></a>
     <?php } ?>
   </p>
 </div>
 <a class="btn" href="javascript:history.back(1)"><i class="icon-chevron-left"></i> <?php echo( GOBACK_MESSAGE );?></a>
 <a class="btn" href="../"><i class="icon-home"></i> <?php echo( GOHOME_MESSAGE );?></a>
<?php } ?>
</div> <!-- /container -->
    <?php include("../javascript.php"); ?>

</body>
</html>