<?php

  include "config.php";
  include "utiles.php";

  //establecemos la conexion con la base de datos...
  $mysqli = new mysqli($sql_servidor, $sql_usuario, $sql_pass, $sql_bbdd);
  if ($mysqli->connect_error) {
    die('Error de conexion('.mysqli->connect_errno.')'.$mysqli->connect_error);
  }

  if ($mysqli_connect_error()){
    die('Error de conexion('.mysqli->connect_errno.')'.$mysqli->connect_error);
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
mysqli_close($mysqli);

//validacion de los datos entrantes
$id_modulo = htmlspecialchars($_GET["id"], ENT_QUOTES);
$temperatura = htmlspecialchars($_GET["temperatura"], ENT_QUOTES);
$humedad = htmlspecialchars($_GET["humedad"], ENT_QUOTES);
$luz = = htmlspecialchars($_GET["luz"], ENT_QUOTES);
$particulas = htmlspecialchars($_GET["particulas"], ENT_QUOTES);
$CO2 = htmlspecialchars($_GET["coo"], ENT_QUOTES);
$CO = htmlspecialchars($_GET["co"], ENT_QUOTES);
$UV = htmlspecialchars($_GET["uv"], ENT_QUOTES);
$lluvia = htmlspecialchars($_GET["lluvia"], ENT_QUOTES);
$viento= htmlspecialchars($_GET["viento"], ENT_QUOTES);
$consumo = htmlspecialchars($_GET["consumo"], ENT_QUOTES);
//$num_personas = htmlspecialchars($_GET[""], ENT_QUOTES);

//Si el modulo devuelve un id valido registramos sus datos
if ($id_modulo!="") {
  $sql = "insert into registros (id_modulo, fecha, hora, temperatura, humedad, luz, particulas, CO2, CO, UV, lluvia, viento, consumo, num_personas)"
          values('$id_modulo','date('Y-m-d')','h:i:s', '$temperatura','$humedad','$luz','$particulas','$CO2','$CO2','$UV','$viento','$consumo','$num_personas');
  if (!mysqli_query($mysqli,$sql)) {
    //Si se produce un fallo lo almacenamos en el fichero de log
    registroLog($fichero_log, mysqli_error($mysqli));
  }
}else {
  //Si el id de registro no es valido almacena el suceso en el fichero de log
  registroLog($fichero_log, "ACCESO INVALIDO");
}
mysqli_close($mysqli);
?>
