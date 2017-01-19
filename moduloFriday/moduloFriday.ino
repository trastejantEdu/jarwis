#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Wire.h>
#include <ESP8266HTTPClient.h>
#include "DHT.h"
#include "SSD1306.h"

#define USE_SERIAL Serial
#define DHTPIN D4
#define WiFi_Logo_width 60
#define WiFi_Logo_height 36
#define DHTTYPE DHT22

ESP8266WiFiMulti WiFiMulti;
SSD1306  display(0x3c, D1, D2);
ESP8266WebServer server ( 80 );
DHT dht(DHTPIN, DHTTYPE);

const char *ssid = "YOURSSID";
const char *password = "YOURPASSWORD";
const int id = ESP.getChipId();

const char WiFi_Logo_bits[] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xFF, 0x07, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xE0, 0xFF, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0xFF,
  0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0xFF, 0xFF, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xFE, 0xFF, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF,
  0xFF, 0x03, 0x00, 0x00, 0x00, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00,
  0x00, 0xFF, 0xFF, 0xFF, 0x07, 0xC0, 0x83, 0x01, 0x80, 0xFF, 0xFF, 0xFF,
  0x01, 0x00, 0x07, 0x00, 0xC0, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x0C, 0x00,
  0xC0, 0xFF, 0xFF, 0x7C, 0x00, 0x60, 0x0C, 0x00, 0xC0, 0x31, 0x46, 0x7C,
  0xFC, 0x77, 0x08, 0x00, 0xE0, 0x23, 0xC6, 0x3C, 0xFC, 0x67, 0x18, 0x00,
  0xE0, 0x23, 0xE4, 0x3F, 0x1C, 0x00, 0x18, 0x00, 0xE0, 0x23, 0x60, 0x3C,
  0x1C, 0x70, 0x18, 0x00, 0xE0, 0x03, 0x60, 0x3C, 0x1C, 0x70, 0x18, 0x00,
  0xE0, 0x07, 0x60, 0x3C, 0xFC, 0x73, 0x18, 0x00, 0xE0, 0x87, 0x70, 0x3C,
  0xFC, 0x73, 0x18, 0x00, 0xE0, 0x87, 0x70, 0x3C, 0x1C, 0x70, 0x18, 0x00,
  0xE0, 0x87, 0x70, 0x3C, 0x1C, 0x70, 0x18, 0x00, 0xE0, 0x8F, 0x71, 0x3C,
  0x1C, 0x70, 0x18, 0x00, 0xC0, 0xFF, 0xFF, 0x3F, 0x00, 0x00, 0x08, 0x00,
  0xC0, 0xFF, 0xFF, 0x1F, 0x00, 0x00, 0x0C, 0x00, 0x80, 0xFF, 0xFF, 0x1F,
  0x00, 0x00, 0x06, 0x00, 0x80, 0xFF, 0xFF, 0x0F, 0x00, 0x00, 0x07, 0x00,
  0x00, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x00, 0xF8, 0xFF, 0xFF,
  0xFF, 0x7F, 0x00, 0x00, 0x00, 0x00, 0xFE, 0xFF, 0xFF, 0x01, 0x00, 0x00,
  0x00, 0x00, 0xFC, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0xFF,
  0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xFF, 0x1F, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x80, 0xFF, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};


String url = "http://192.168.1.33/FRIDAY/registrador.php?id=";
int progress;
int frecuencia = 10000;

void setup() {

    display.init();
    display.drawXbm(34, 0, WiFi_Logo_width, WiFi_Logo_height, WiFi_Logo_bits);
    display.display();
    USE_SERIAL.begin(115200);
   // USE_SERIAL.setDebugOutput(true);

    USE_SERIAL.println();
    USE_SERIAL.println();
    USE_SERIAL.println();

    /**
    for(uint8_t t = 4; t > 0; t--) {
        USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
        USE_SERIAL.flush();
        delay(1000);
    }
    **/
    WiFiMulti.addAP("MOVISTARTL", "Martin89");

  while ( WiFi.status() != WL_CONNECTED ) {
    progress= progress + 20;
    delay ( 500 );
    Serial.print ( "." );
    //display.print(".");
    if(progress>=100) progress=0;
    display.drawProgressBar(0, 52, 120, 10, progress);
    display.display();
  }

 Serial.println ( "" );
 Serial.print ( "Connected to " );
 Serial.println ( ssid );
 Serial.print ( "IP address: " );
 Serial.println ( WiFi.localIP() );
 
 if ( MDNS.begin ( "esp8266" ) ) {
  Serial.println ( "MDNS responder started" );
 }

 Serial.println ( "HTTP server started" );
 display.clear();
}

void loop() {
  //Lectura de sensores y actualización de la hora
  int humedad = dht.readHumidity();
  String humedadNow = String(humedad); 
  int hora = 12;
  int minuto = 10;

  //cast de los datos obtenidos para motrarlos por pantalla
  int temperatura = dht.readTemperature();
  String temperaturaNow = String(temperatura); 
  String horaNow = String(hora);
  String minutoNow = String(minuto);

  //Mostramos por pantalla la información
  display.clear();
 display.setTextAlignment(TEXT_ALIGN_CENTER);
 display.setFont(ArialMT_Plain_16);
    display.drawString(60, 0, "Jarvis");
    display.drawHorizontalLine(5, 17, 110);
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_10);
    display.drawString(0, 20, "En:");
    display.drawString(30, 20, ssid);
    display.setFont(ArialMT_Plain_10);
    display.drawString(0, 30, "IP:");
    display.drawString(15, 30, WiFi.localIP().toString());

    display.drawString(0, 50, "T:");
    display.drawString(10, 50, temperaturaNow);
    display.drawString(23, 50, "ºC");
    display.drawString(50, 50, "H:");
    display.drawString(60, 50, humedadNow);
    display.drawString(70, 50, "%");
    display.drawString(90, 50, horaNow);
    display.drawString(105, 50, ":");
    display.drawString(110, 50, minutoNow);
    display.display();
    //delay(500);
    
    //Si tenemos conexión a internet enviamos los datos al servidor
    if((WiFiMulti.run() == WL_CONNECTED)) {
        
        HTTPClient http;

        USE_SERIAL.print("[HTTP] begin...\n");
        
        //Envia la info para ser almacenada en el servidor
        url = url += id;
        url = url += "&temperatura=";
        url = url += temperaturaNow;
        url = url += "&humedad=";
        url = url += humedadNow;
        
        http.begin(url);

        //Respuesta del servidor (¡¡IMPLEMENTAR SISTEMA DE COMPROBACIÓN!!)
        USE_SERIAL.print("[HTTP] GET...\n");
      
        int httpCode = http.GET();

        // httpCode will be negative on error
        if(httpCode > 0) {
            // HTTP header has been send and Server response header has been handled
            USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);

            // file found at server
            if(httpCode == HTTP_CODE_OK) {
                String payload = http.getString();
                USE_SERIAL.println(payload);
            }
        } else {
            USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }
        //Cierra la conexion
        http.end();
    }

    delay(frecuencia);
}

