<?php
function registroLog($fichero,$log){
  $fecha = date('l jS \of F Y h:i:s A');
  $log = $fecha." - ".$log;
  $file = fopen("log.txt", "w");
  fwrite($file, $log . PHP_EOL);
  fclose($file);
}
?>
