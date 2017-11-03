<?php
include "confi.php";
include "utiles.php";
error_reporting(-1);
//establecemos la conexion con la base de datos...
$mysqli = new mysqli($sql_servidor, $sql_usuario, $sql_pass, $sql_bbdd);

if ($mysqli->connect_errno) {
  echo "Error de conexion(".$mysqli->connect_errno.")".$mysqli->connect_error;

}

if (mysqli_connect_error()){
  die('Error de conexion('.$mysqli->connect_errno.')'.$mysqli->connect_error);
}
?>

<!DOCTYPE html>
<html lang="en" class="no-js">
	<head>
		<meta charset="UTF-8" />
		<meta http-equiv="X-UA-Compatible" content="IE=edge,chrome=1">
		<meta name="viewport" content="width=device-width, initial-scale=1.0">
		<title>F.R.I.D.A.Y. - Datos</title>
		<meta name="description" content="Circular Navigation Styles - Building a Circular Navigation with CSS Transforms | Codrops " />
		<meta name="keywords" content="css transforms, circular navigation, round navigation, circular menu, tutorial" />
		<meta name="author" content="Sara Soueidan for Codrops" />
		<link rel="shortcut icon" href="../favicon.ico">
		<link rel="stylesheet" type="text/css" href="css/normalize.css" />
		<link rel="stylesheet" type="text/css" href="css/demo.css" />
		<link rel="stylesheet" type="text/css" href="css/component1.css" />
		<script src="js/modernizr-2.6.2.min.js"></script>

<script type="text/javascript">
var _gaq = _gaq || [];
_gaq.push(['_setAccount', 'UA-7243260-2']);
_gaq.push(['_trackPageview']);
(function() {
var ga = document.createElement('script'); ga.type = 'text/javascript'; ga.async = true;
ga.src = ('https:' == document.location.protocol ? 'https://ssl' : 'http://www') + '.google-analytics.com/ga.js';
var s = document.getElementsByTagName('script')[0]; s.parentNode.insertBefore(ga, s);
})();
</script>
<?php 	//$sql = mysqli_query($mysqli,"SELECT * FROM registros ORDER BY fecha, hora DESC LIMIT 20"); ?>
<script type="text/javascript" src="https://ajax.googleapis.com/ajax/libs/jquery/1.8.2/jquery.min.js"></script>
<style type="text/css">
${demo.css}
</style>
<script type="text/javascript">
$(function () {
Highcharts.chart('container', {
    chart: {
        type: 'line'
    },
    title: {
        text: 'Registros de temperaturas'
    },
    subtitle: {
        text: 'Source: Jarvis'
    },
    xAxis: {
        categories: ['Ene', 'Feb', 'Mar', 'Abr', 'May', 'Jun', 'Jul', 'Ago', 'Sep', 'Oct', 'Nov', 'Dic']
    },
    yAxis: {
        title: {
            text: 'Temperature (°C)'
        }
    },
    plotOptions: {
        line: {
            dataLabels: {
                enabled: true
            },
            enableMouseTracking: false
        }
    },
    series: [
      {
        name: 'Exterior',
        data: [
      <?php
      $sql = mysqli_query($mysqli,"SELECT AVG(temperatura) FROM registros WHERE id_modulo = 0 GROUP BY fecha");
      //mysqli_fetch_array($sql);
      $i = 0;
      if ($row = mysqli_fetch_array($sql)) {
        do{
        //  $temp = $row["temperatura"];
          //echo $media.=",";
          echo $row[$i].=",";
          $i = $i++;
        }while ($row = mysqli_fetch_array($sql));
    }
    mysqli_free_result ($sql)
      ?>
    ]}, {
        name: 'Habitacion Nano',
        data: [
          <?php
          $sql = mysqli_query($mysqli,"SELECT AVG(temperatura) FROM registros WHERE id_modulo = 13944538 GROUP BY fecha");

          $i = 0;
          if ($row = mysqli_fetch_array($sql)) {
            do{
              echo $row[$i].=",";
              $i = $i++;
            }while ($row = mysqli_fetch_array($sql));
        }else{echo "-10";}
          ?>
        ]},
    {
        name: 'Salon',
        data: [5.9, 2.2, 3.7, 5.5, 1.9, 5.2, 7.0, 6.6, 1.2, 0.3, 4.6, 5.8]
    }]
});
});
</script>

	</head>

<style>

table{
  margin: 0 0 40px 0;
  width: 100%;
  box-shadow: 0 1px 3px rgba(0,0,0,0.2);
  display: table;
}
  @media screen and (max-width: 580px){
    display: block;
}

tr{
  display: table-row;
  background: #f6f6f6;
  &:nth-of-type(odd)
    background: #e9e9e9;
  &.header
    font-weight: 900;
    color: #ffffff;
    background: #ea6153;
  &.green
    background: #27ae60;
  &.blue
    background: #2980b9;
  }

  @media screen and (max-width: 580px){
    padding: 8px 0;
    display: block;
}

td{
  padding: 6px 12px;
  display: table-cell;
}
  @media screen and (max-width: 580px){
    padding: 2px 12px;
    display: block;
}

th{

	padding:20px;

}
</style>
	<body>
		<div class="container">
			<!-- Top Navigation -->
			<div class="codrops-top clearfix">
				<a class="codrops-icon codrops-icon-prev" href="index.html"><span>Inicio</span></a>
				<span class="right"><a class="codrops-icon codrops-icon-drop" href="logout.php"><span>Salir</span></a></span>
			</div>
			<header>
				<h1>F.R.I.D.A.Y.<span>by CrakerNano</span></h1>
				<nav class="codrops-demos">
					<a class="current-demo" href=".">Inicio</a>
					<a href="historico.php">Registro</a>
					<a href="restart.php">Reinciar</a>
				</nav>
			</header>

			<!--
			<style type="text/css">
				.menu{
					float:left; width:20%;
					background:#000000;
					min-height: 40%;
				}
			</style>
			<div class="menu">
			<h2>Filtros</h2>
			</div>
			-->
			<section>

      <script src="https://code.highcharts.com/highcharts.js"></script>
      <script src="https://code.highcharts.com/modules/exporting.js"></script>

      <div id="container" style="min-width: 310px; height: 400px; margin: 0 auto"></div>

				<?php
				$sql = mysqli_query($mysqli,"SELECT * FROM registros ORDER BY id DESC LIMIT 20");

				if ($row = mysqli_fetch_array($sql)) {
				?>
				<table>

				  <tr>
				          <th>id_modulo</th>
				          <th>fecha</th>
				          <th>hora</th>
				          <th>temperatura</th>
				          <th>humedad</th>
				          <th>luz</th>
				          <th>particulas</th>
				          <th>CO</th>
				          <th>CO2</th>
				          <th>UV</th>
				          <th>lluvia</th>
				          <th>viento</th>
				          <th>consumo</th>
				          <th>num_personas</th>
				        </tr>
				<?php
          $nc = "-";
				  do{
				    echo "<tr>
				            <td>".$row["id_modulo"]."</td>
				            <td>".$row["fecha"]."</td>
				            <td>".$row["hora"]."</td>
				            <td>".$row["temperatura"]."</td>
				            <td>".$row["humedad"]."</td>
				            <td>".$row["luz"]."</td>
				            <td>".$row["particulas"]."</td>
				            <td>".$row["CO"]."</td>
				            <td>".$row["CO2"]."</td>
				            <td>".$row["UV"]."</td>
				            <td>".$row["lluvia"]."</td>
				            <td>".$row["viento"]."</td>
				            <td>".$row["consumo"]."</td>
				            <td>".$row["num_personas"]."</td>
				          </tr>
				    ";
				  }while ($row = mysqli_fetch_array($sql));


				} else {
				  echo "<tr><td>NO HAY DATOS QUE MOSTRAR<td><tr>";
				}

				 ?>

			</section>
			<div class="component">
				<!--con Start Nav Structure -->
				<button class="cn-button" id="cn-button">+</button>
				<div class="cn-wrapper" id="cn-wrapper">
				    <ul>
				      <li><a href="datos.php"><span class="icon-picture"></span></a></li>
				      <li><a href=".php"><span class="icon-headphones"></span></a></li>
				      <li><a href="."><span class="icon-home"></span></a></li>
				      <li><a href="controles.php"><span class="icon-facetime-video"></span></a></li>
				      <li><a href="configuracion.php"><span class="icon-envelope-alt"></span></a></li>
				     </ul>
				</div>
				<div id="cn-overlay" class="cn-overlay"></div>
				<!-- End Nav Structure -->
			</div>
		</div><!-- /container -->
		<script src="js/polyfills.js"></script>
		<script src="js/demo1.js"></script>
		<!-- For the demo ad only -->
<script src="http://tympanus.net/codrops/adpacks/demoad.js"></script>
	</body>
</html>
