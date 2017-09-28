#ifndef CONFIGURATION_H
#define CONFIGURATION_H

//Datos de la red Wifi
const char *ssid = "sindormir.net";
const char *password = "espaciomiscela";

//URL del servidor Jarvis
String url = "http://192.168.1.33/FRIDAY/registrador.php?id=";

//Frecuencia de refresco de las mediciones
int frecuencia = 10000;

//Horario de verano España
int UTC = 2;

//Configuración del display
bool flipDisplay = true;//Posicion del display. Normal -> FALSE. Invertida->True

#endif // CONFIGURATION_H
