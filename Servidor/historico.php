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
<html>
<head><title>REGISTROS - FRIDAY</title></head>
<body>


<?php
$sql = mysqli_query($mysqli,"SELECT * FROM registros");

if ($row = mysqli_fetch_array($sql)) {
?>
<table>

  <tr>
          <th>id_modulo</th>
          <th>fecha</th>
          <th>hora</t>
          <th>temmperatura</th>
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
 </table>
 </body>
 </html>
