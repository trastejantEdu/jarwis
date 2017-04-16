<!DOCTYPE html>
<html lang="en" class="no-js">
	<head>
		<meta charset="UTF-8" />
		<meta http-equiv="X-UA-Compatible" content="IE=edge,chrome=1"> 
		<meta name="viewport" content="width=device-width, initial-scale=1.0"> 
		<title>Circular Navigation - Demo 1 | Codrops</title>
		<meta name="description" content="Circular Navigation Styles - Building a Circular Navigation with CSS Transforms | Codrops " />
		<meta name="keywords" content="css transforms, circular navigation, round navigation, circular menu, tutorial" />
		<meta name="author" content="Sara Soueidan for Codrops" />
		<link rel="shortcut icon" href="../favicon.ico">
		<link rel="stylesheet" type="text/css" href="css/normalize.css" />
		<link rel="stylesheet" type="text/css" href="css/demo.css" />
		<link rel="stylesheet" type="text/css" href="css/component1.css" />
		<link rel="stylesheet" type="text/css" href="css/tablas.css" />
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
				<h1>Administracion<span>by CrakerNano</span></h1>	
				<nav class="codrops-demos">
					<a class="current-demo" href=".">Inicio</a>
					<a href="colegios.php">Nube privada</a>
					<a href="agenda.php">Agenda</a>
				</nav>
			</header>
			<style type="text/css">
				.menu{
					float:left; width:20%; 
					background:#000000; 
					min-height: 40%;
					margin-right: 3%;
					padding-bottom: 2%;

				}

				.menu h2{
					text-align: center;
					text-decoration: inherit;
				}

				.menu h3{
					margin-top: 5%;
				}

				.menu label{
					display: block;
				}
			</style>
			<div class="menu">
			<h2>Filtros</h2><hr>
			<form>
				<h3>Ubicacion</h3>
				<select name="ubicacion">
				   <option selected value="0"> Elige una opción </option>
				       <optgroup label="Colegio"> 
				       <option value="1">Sta Maria la Blanca</option> 
				       <option value="2">St. Annes School</option> 
				       <option value="3">Humanitas</option> 
				   </optgroup> 
				   <optgroup label="Otros centros"> 
				       <option value="10">Se aceptan ideas</option> 
				       <option value="11">Garaje</option> 
				       <option value="12">American Space</option> 
				   </optgroup> 
				</select>
				<h3>Estado</h3>
         		 <input type = "radio"
	                 name = "radSize"
	                 id = "sizeSmall"
	                 value = "small"
	                 checked = "checked" />
		          <label for = "sizeSmall">Funcional</label>
		          
		          <input type = "radio"
		                 name = "radSize"
		                 id = "sizeMed"
		                 value = "medium" />
		          <label for = "sizeMed">Necesita revision</label>		 
		          
			</form>
			

			</div>
			<section>
				<table>
					<tr><td>#</td><td>ID</td><td>Tipo</td><td>Estado</td></tr>
					<tr><td>#</td><td>CampWeDo02</td><td>WeDo</td><td>Completo</td></tr>
					<tr><td>#</td><td>CampWeDo05</td><td>WeDo</td><td>Incompleto</td></tr>
					<tr><td>#</td><td>CampWeDo02</td><td>WeDo</td><td>Completo</td></tr>
				</table>
			</section>
			<div class="component">
				<!-- Start Nav Structure -->
				<button class="cn-button" id="cn-button">+</button>
				<div class="cn-wrapper" id="cn-wrapper">
				    <ul>
				      <li><a href="materiales.php"><span class="icon-picture"></span></a></li>
				      <li><a href="rrhh.php"><span class="icon-headphones"></span></a></li>
				      <li><a href="."><span class="icon-home"></span></a></li>
				      <li><a href="colegios.php"><span class="icon-facetime-video"></span></a></li>
				      <li><a href="centros.php"><span class="icon-envelope-alt"></span></a></li>
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