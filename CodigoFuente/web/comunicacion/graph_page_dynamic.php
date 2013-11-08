<?php
if (!isset($_SESSION)) {
	session_start();
}
include("../init.php");
?><?php
writeheader(HOME_DESCRIP,KEYWORDS_MESSAGE);
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
				url: '../cgi-bin/recibir_linux_json.py?puerto=<?php echo $_SESSION['puerto']; ?>&velocidad=<?php echo $_SESSION['velocidad']; ?>&databit=<?php echo $_SESSION['databit']; ?>&stopbit=<?php echo $_SESSION['stopbit']; ?>&paridad=<?php echo $_SESSION['paridad']; ?>&control=<?php echo $_SESSION['control']; ?>',
<?php } ?>
<?php if (isset($_SESSION['OS']) && $_SESSION['OS']=="WINDOWS")
{ ?>
				url: '../cgi-bin/recibir_windows_json.py?puerto=<?php echo $_SESSION['puerto']; ?>&velocidad=<?php echo $_SESSION['velocidad']; ?>&databit=<?php echo $_SESSION['databit']; ?>&stopbit=<?php echo $_SESSION['stopbit']; ?>&paridad=<?php echo $_SESSION['paridad']; ?>&control=<?php echo $_SESSION['control']; ?>',
				/*url: 'json_data.php',*/
<?php } ?>
<?php if (!isset($_SESSION['OS']))
{ 
	echo ERROR_OSNOT_DETECTED_MESSAGE2;
}
?>
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
					text: 'Live data from AP'
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
</head>
<body>
<?php include("../menu.php"); ?>
<div class="container">
<h1>Access Point Graph <small><?php echo( READ ); ?></small></h1>
<script src="../js/highcharts.js"></script>
<script src="../js/exporting.js"></script>
<div id="container" style="min-width: 400px; height: 400px; margin: 0 auto"></div>
</div>

    <?php include("../javascript.php"); ?>

</body>
</html>