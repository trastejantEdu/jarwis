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
		<title>F.R.I.D.A.Y. - Inicio</title>
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

	</head>
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
					<a href="colegios.php">Nube privada</a>
					<a href="agenda.php">Apagar todo</a>
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
				<?php
				$sql = mysqli_query($mysqli,"SELECT * FROM modulos");

				if ($row = mysqli_fetch_array($sql)) {

					do{
						$id_modulo = $row["id_modulo"];
						$consulta = mysqli_query($mysqli,"SELECT * FROM registros ORDER BY id DESC LIMIT 1 WHERE 'id_modulo' = ".$id_modulo);
						if ($mod = mysqli_fetch_array($consulta)) { 
							echo $row["ubicacion"];
						do{
							echo $$id_modulo;
							echo $mod["temperatura"];
							echo $mod["humedad"];
						}while ($row = mysqli_fetch_array($consulta));
						}
					}while ($row = mysqli_fetch_array($sql));
				}
				?>
			</section>
			<div class="component">
				<!--con Start Nav Structure -->
				<button class="cn-button" id="cn-button">+</button>
				<div class="cn-wrapper" id="cn-wrapper">
				    <ul>
				      <li><a href="datos.php"><span class="icon-picture"></span></a></li>
				      <li><a href="multimedia.php"><span class="icon-headphones"></span></a></li>
				      <li><a href="."><span class="icon-home"></span></a></li>
				      <li><a href="seguridad.php"><span class="icon-facetime-video"></span></a></li>
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
