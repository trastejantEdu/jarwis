#ifndef CONFIGURATION_H
#define CONFIGURATION_H

//Datos de la red Wifi
//const char *ssid = "YourSSID";
//const char *password = "YourWiFiPassword";

//URL del servidor Jarvis
String url = "http://192.168.0.33/FRIDAY/registrador.php?id=";

//Frecuencia de refresco de las mediciones
int frecuencia = 1800000;

//Horario de verano España
int UTC = 2;

//Configuración del display
bool flipDisplay = true;//Posicion del display. Normal -> FALSE. Invertida->True

//Es un slice
bool slice = true;

//Habilita la subida de datos al servidor jarvis
bool jarvisSync=true;

//
#define MAX_SYNC_ERROR 3


#endif // CONFIGURATION_H
