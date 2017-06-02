#include <ESP8266WebServer.h>

String web = "<!DOCTYPE HTML><html><head><title>Lampara</title></head><body><h1> <FONT SIZE=\"5\" COLOR=\"red\"> Colores </h1>Selecciona un color: <form action=\"\"><input name=\"color\" type=\"color\" style='width:300px; height:300px'/><input name=\"intensidad\" type=\"range\" style='width:80%; height:300px'/><br><input type=\"submit\" value=\"Cambiar\" style='width:100px; height:50px'/></form></body></html>";

void handleRoot() {
  String colores;
  server.method() == HTTP_GET;
  digitalWrite(led, 1);
  server.send(200, "html", web);
  digitalWrite(led, 0);
  Serial.print("Argumentos:");
  Serial.println(server.args());
  Serial.print("URI:");
  Serial.println(server.uri());
  for (uint8_t i=0; i<server.args(); i++){
    colores += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  Serial.println(colores);
  
  //Busca el comienzo del codigo hexadecimal de color
  int firstHastag = colores.indexOf('#');
  Serial.print("Primera respuesta: ");Serial.println(firstHastag);
  
  //Extrae los colores codificados en Hexadecimal en R-G-B
  R = colores.substring(firstHastag+1, firstHastag+3);
  G = colores.substring(firstHastag+3, firstHastag+5);
  B = colores.substring(firstHastag+5, firstHastag+7);
  Serial.print("Color en Hex: ");Serial.print(R);Serial.print("-"); Serial.print(G);Serial.print("-");Serial.println(B);
  
  //Convierte los valores de color hexadecimales en decimales
  R = hexToDec(R);
  G = hexToDec(G);
  B = hexToDec(B);  
  Serial.print("Color en RGB: ");Serial.print(R);Serial.print("-"); Serial.print(G);Serial.print("-");Serial.println(B);
  
  //Transforma el String en valores integer
  Ri = R.toInt();
  Gi = G.toInt();
  Bi = B.toInt();

  //Obtenemos la intensidad
  int findIntensidad = colores.indexOf('intensidad');
  int ultPos = colores.length();
  //int ultPos = colores.lastIndexOf('/');
  Serial.print("Comienza la cadena");Serial.println(findIntensidad);Serial.print("Posicion");Serial.println(ultPos);
  intensidad = colores.substring(findIntensidad+4,ultPos-1);
  Ii = intensidad.toInt();
  Serial.print("Intensidad: ");Serial.println(intensidad);
  Serial.print("I: ");Serial.println(Ii);
  
  //mapeamos los valores del range HTML5 (0 a 100) a brightness de Neopixel (0 a 255)
  Ii = map(Ii, 0, 100, 0, 255);
  Serial.print("Intensidad mapeada: ");Serial.println(Ii);
  
  //Encendemos la luces en el color seleccionado
  iluminacion(Ri,Gi,Bi,Ii);
 
}

void handleNotFound(){
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}
