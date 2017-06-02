#ifndef CONFIGURATION_H
#define CONFIGURATION_H

//Datos de la red Wifi
const char *ssid = "MOVISTAR_501E";
const char *password = "DxuYySmC4h7L9PXZ7GM8";

//URL del servidor Jarvis
String url = "http://192.168.1.33/FRIDAY/registrador.php?id=";

//Frecuencia de refresco de las mediciones
int frecuencia = 10000;

//Horario de verano España
int UTC = 2;

#endif // CONFIGURATION_H
