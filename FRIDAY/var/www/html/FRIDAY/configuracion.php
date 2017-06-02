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
	</head>

<style>


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

      <div class="modulos_activos">
        <?php
        $sql = mysqli_query($mysqli,"SELECT * FROM modulos");

        if ($row = mysqli_fetch_array($sql)) {
        ?>
        <table>
        <?php
        do{
          echo "<tr>
                  <td>".$row["id_modulo"]."</td>
                  <td>".$row["ubicacion"]."</td>
                </tr>
          ";
        }while ($row = mysqli_fetch_array($sql));
      ?>
      </table>
      <?php

      } else {
        echo "<p>NO HAY DATOS QUE MOSTRAR</p>";
      }

       ?>
       <form action="altaModulo.php" method="POST" name="altaModulo_frm">
          <input type="text" id="id_modulo" name = "id_modulo" placeholder="ID del Modulo" required/>
          <input type="text" id="ubicacion" name = "ubicacion" placeholder="ubicacion" required/>
          <p><input type="submit" name ="activar"> </p>
        </form>
      </div>
			<section>

      <script src="https://code.highcharts.com/highcharts.js"></script>
      <script src="https://code.highcharts.com/modules/exporting.js"></script>

      <div id="container" style="min-width: 310px; height: 400px; margin: 0 auto"></div>



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
