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

//revisa la tabla, la crea si no existe
  $sql = "CREATE TABLE IF NOT EXISTS 'registros'(
    'id'  int NOT NULL AUTO_INCREMENT,
    PRIMARY KEY (id),
    id_modulo int NOT NULL,
    fecha date NOT NULL,
    hora time NOT NULL,
    temperatura int,
    humedad int,
    luz int,
    particulas int,
    CO2 int,
    CO int,
    UV int,
    lluvia int,
    viento int,
    consumo int,
    num_personas int
  )";

mysqli_query($mysqli, $sql);
//mysqli_close($mysqli);

//validacion de los datos entrantes

if(!isset($_GET["luz"])){
  $luz = 0;
}else{
  $luz = htmlspecialchars($_GET["luz"], ENT_QUOTES);
}

if (!isset($_GET["particulas"])) {
  $particulas = -1;
}else {
  $particulas = htmlspecialchars($_GET["particulas"], ENT_QUOTES);
}

if (!isset($_GET["coo"])) {
  $CO2 = -1;
} else {
  $CO2 = htmlspecialchars($_GET["coo"], ENT_QUOTES);
}

if (!isset($_GET["co"])) {
  $CO = -1;
}else {
  $CO = htmlspecialchars($_GET["co"], ENT_QUOTES);
}

if (!isset($_GET["uv"])) {
  $UV = -1;
} else {
  $UV = htmlspecialchars($_GET["uv"], ENT_QUOTES);
}

if (!isset($_GET["lluvia"])) {
  $lluvia = -1;
} else {
  $lluvia = htmlspecialchars($_GET["lluvia"], ENT_QUOTES);
}

if (!isset($_GET["viento"])) {
  $viento = -1;
} else {
  $viento= htmlspecialchars($_GET["viento"], ENT_QUOTES);
}

if (!isset($_GET["consumo"])) {
  $consumo = -1;
} else {
  $consumo = htmlspecialchars($_GET["consumo"], ENT_QUOTES);
}

if (!isset($_GET["npersonas"])) {
  $num_personas = -1;
} else {
  $num_personas = htmlspecialchars($_GET["npersonas"], ENT_QUOTES);
}

if (!isset($_GET["temperatura"])) {
  $temperatura=-99;
} else {
  $temperatura = htmlspecialchars($_GET["temperatura"], ENT_QUOTES);
}

if (!isset($_GET["humedad"])) {
  $humedad = -1;
} else {
  $humedad = htmlspecialchars($_GET["humedad"], ENT_QUOTES);
}

echo $temperatura;


//Si el modulo devuelve un id valido registramos sus datos
if (isset($_GET["id"]) AND $_GET["id"]!="") {
  echo "Almacenando en la base de datos...";
  echo date('h:i:s');
  $id_modulo = htmlspecialchars($_GET["id"], ENT_QUOTES);
  $hora = date('h:i:s');
  $fecha = date('Y-m-d');

  $sql = "insert into registros (id_modulo, fecha, hora, temperatura, humedad, luz, particulas, CO2, CO, UV, lluvia, viento, consumo, num_personas
          )values('".$id_modulo."','".$fecha."','".$hora."', '".$temperatura."','".$humedad."','".$luz."','".$particulas."','".$CO2."','".$CO."','".$UV."','".$lluvia."','".$viento."','".$consumo."','".$num_personas."')";
  if (!mysqli_query($mysqli,$sql)) {
    //Si se produce un fallo lo almacenamos en el fichero de log
    registroLog($fichero_log, mysqli_error($mysqli));
    echo "Error: ".mysqli_error($mysqli);
  }else {
    echo "Alamacenado correctamente";
  }
}else {
  //Si el id de registro no es valido almacena el suceso en el fichero de log
  echo "El modulo no tiene permiso para acceder";
  registroLog($fichero_log, 'ACCESO INVALIDO');
}
mysqli_close($mysqli);
?>

<!DOCTYPE html>
<html>
<head><title>Crear registros</title></head>
<body>
  <p>Crear registro...</p>
</body>
</html>
