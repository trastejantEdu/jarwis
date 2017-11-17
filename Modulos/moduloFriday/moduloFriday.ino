#include <Time.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Wire.h>
#include <ESP8266HTTPClient.h>


#include "SSD1306.h"
#include "confi.h"
#include "NTP.h"
#include "OLED_Display.h"
#include "web.h"
#include "conexion.h"
#include "saveData.h"
#include "menus.h"

#define USE_SERIAL Serial



NTP ntp;


const int id = ESP.getChipId();


//inicializacion con valores no validos
int hora = 25;
int minuto= 62;
int segundo = 62;

void confHora(){
  while ( hora > 24 ){hora = ntp.get_hour();}
  while ( minuto > 60 ){minuto = ntp.get_minutes();}
  while ( segundo > 60 ){segundo = ntp.get_secons();}
  hora = hora + UTC;//Implementar deteccion de horairo de verano/invierno
  setTime(hora,minuto,segundo,16,04,2017);//¡Implentar la getFecha en la libreria NTP!  
}

String return_hora(){
  time_t t = now();  
  return String(hour(t))+":"+String(minute(t));
}

void setup() {

    inicializarDisplay(flipDisplay);
    wifiLogo();
    
    //Inicializar puerto serial
    USE_SERIAL.begin(115200);
    USE_SERIAL.println();
    USE_SERIAL.println();
    USE_SERIAL.println();
    
 conexionWiFi();
 //Serial.println("Chip ID: "+ id); 
 ntp.begin();
 confHora();
 Serial.println("HORA SINCRONIZADA");
 sensorBegin();
 Serial.println("SENSOR INICIALIZADO");

 initMenus();
 
 if ( MDNS.begin ( "esp8266" ) ) {
  Serial.println ( "MDNS responder started" );
 }

  //Configuracion de la navegacion
  server.on("/", bienvenida);
  server.on("/control", control);
  server.on("/lecturas", lecturas);
  server.on("/about", about);
  

 //Inicializacion del servidor web
 server.begin();
 rgb_begin();
 
 Serial.println ( "HTTP server started" );
 display.clear();
 
 String ssid_str = String(ssid);
 pantalla_info(id,ssid_str, WiFi.localIP().toString());
 delay(3000);
}//Fin de la función Setup

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= frecuencia) {
  //Lectura de sensores   
  Serial.print("H:");
  Serial.println(readHumedadStr());
  Serial.print("T:");
  Serial.println(readTemperaturaStr());
 
 //Menus
 if(estado==1){
  mostrarMenu();
 }else{
   pantalla_datos(return_hora(), readTemperatura(), readHumedad());
 }
  
 
    
    //Si tenemos conexión a internet enviamos los datos al servidor
  saveData(id);

  }
    
    server.handleClient();
}

