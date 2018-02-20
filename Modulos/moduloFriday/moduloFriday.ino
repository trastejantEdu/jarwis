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

int SyncError= 0;
int epoch=-1;
long previousTime = 0;

NTP ntp;

const int id = ESP.getChipId();

unsigned long currentMillis;

String return_hora(){
  time_t t = now();  
  int hora = hour(t)+ntp.ajusteHorario(day(t),month(t),year(t), hour(t), minute(t),second(t));
  return String(hora)+":"+String(minute(t));
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
 

 //Poner el reloj en hora
 display.drawString(60, 70, "Obteniendo hora...");
 display.display();
 ntp.begin();
 int progress = 0;

 
 //while (ntp.onTime() == -1) {
 while (epoch == -1) {
    epoch = ntp.onTime();
    delay (500);
    Serial.print ( "#" );
    display.drawProgressBar(0, 100, 120, 10, progress);
    progress++;
    display.display();
  }

    int hora = ntp.get_hour(epoch);
    int minuto = ntp.get_minutes(epoch);
    int segundo = ntp.get_secons(epoch);
    setTime(hora,minuto,segundo,ntp.get_day(),ntp.get_month(),ntp.get_year());
  
  
  
  
 //confHora();
 Serial.println("HORA SINCRONIZADA");
 Serial.print("Hora del NTP: ");
 Serial.println(String(hora)+":"+String(minuto)+":"+String(segundo));
 Serial.print("Hora corregida: ");
 Serial.println(return_hora());

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
 
 
 Serial.println ( "HTTP server started" );

 //Iniciamos la lampara
 rgb_begin();
 Serial.println("Librerias RGB started");
 display.clear();
 
 String ssid_str = String(ssid);
 pantalla_info(id,ssid_str, WiFi.localIP().toString());
 delay(3000);
}//Fin de la función Setup

void loop() {

  currentMillis = currentMillis + millis();  
  
  if (currentMillis >= frecuencia) {
  
  //Lectura de sensores   
  Serial.print("H:");
  Serial.println(readHumedadStr());
  Serial.print("T:");
  Serial.println(readTemperaturaStr());

    if(WiFi.status()&&jarvisSync){
        //Si tenemos conexión a internet enviamos los datos al servidor
      if(!saveData(id)){
        //incre el contador de errores
         SyncError++;
         if(SyncError>MAX_SYNC_ERROR){restart();}//Si suceden 3 sincronizadores fallidas reinicia
      }
    }
  }
 
 //Menus
 if(estado==1){
  mostrarMenu();
 }else{
   pantalla_datos(return_hora(), readTemperatura(), readHumedad());
 }
  
  server.handleClient();
}

