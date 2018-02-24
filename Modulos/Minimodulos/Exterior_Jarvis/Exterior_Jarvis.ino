#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>
#include <BH1750.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "DHT.h"
#include "saveData.h"
#include "conf.h"

#define SENSORPIN D8
#define DHTTYPE DHT22
#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);
BH1750 luxometro;
DHT sensor(SENSORPIN, DHTTYPE);
ESP8266WebServer server(80);

const int id = ESP.getChipId();


unsigned long previousMillis = 0;  
 
const byte luxMode = BH1750_CONTINUOUS_HIGH_RES_MODE;
float temperature;



const char* ssid = "yourSSID";
const char* password = "YOURWiFiPassword";

// Muestra las características del sensor
void displaySensorDetails(void){
  sensor_t sensor;
  bmp.getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.print  ("Sensor: ");
  Serial.println(sensor.name);
  Serial.print  ("Driver: ");
  Serial.println(sensor.version);
  Serial.print  ("ID: ");
  Serial.println(sensor.sensor_id);
  Serial.print  ("Max Valor: ");
  Serial.print(sensor.max_value);
  Serial.println(" hPa");
  Serial.print  ("Min Valor: ");
  Serial.print(sensor.min_value);
  Serial.println(" hPa");
  Serial.print  ("Resolucion: ");
  Serial.print(sensor.resolution);
  Serial.println(" hPa");
  Serial.println("------------------------------------");
  Serial.println("");
  delay(1000);
}

void showSerial(int timeDelay){
   
  

  // Muestra los resultados
    // Obtiene un nuevo evento del sensor
  sensors_event_t event;
  bmp.getEvent(&event);
  if (event.pressure) {
    // Muestra la presión atmosférica en hPa
    Serial.print("Presion: ");
    Serial.print(event.pressure);
    Serial.println(" hPa");
    // Obtenemos la temperatura
    
    bmp.getTemperature(&temperature);
    Serial.print("Temperatura: ");
    Serial.print(temperature);
    Serial.print(" C (");
    Serial.print(sensor.readTemperature());
    Serial.println(" C)");
    Serial.print("Humedad: ");
    Serial.print(sensor.readHumidity());
    Serial.println("%");
    
    // Cálculo de la altura
    float seaLevelPressure = SENSORS_PRESSURE_SEALEVELHPA;
    Serial.print("Altitud: ");
    Serial.print(bmp.pressureToAltitude(seaLevelPressure, event.pressure));
    Serial.println(" m");
    Serial.println("");
  }
  else {
    Serial.println("Error en el sensor");
  }

   uint16_t lux = luxometro.readLightLevel(); // Lectura del BH1750
   Serial.print(F("Iluminancia:  "));
   Serial.print(lux);
   Serial.println(" lx");
  delay(timeDelay); // Muestras cada 20 seg.
}

void datos(){
  sensors_event_t event;
  bmp.getEvent(&event);              
  bmp.getTemperature(&temperature);
  
  String weblecturas ="<!doctype html> <html> <head> <meta charset='utf-8'/> <meta name=description content='Resumen del contenido de la página'> <title>Estacion meteorologica</title> ";
  weblecturas =weblecturas+"<style type=text/css>h2{text-shadow:1px 2px #999;font-size:30px}header{background:#097293;padding:20px;border-top-left-radius:35px;border-top-right-radius:15px;text-align:center;color:#eee}nav{margin:2% auto 2% 40%}nav a{text-decoration:none;padding-right:40px;color:black}nav a:visited{color:black}section{width:80%;margin:8% auto;background-color:white;padding:8px;border-right:black 1px solid;border-left:black 1px solid;border-top-left-radius:20px;border-top-right-radius:20px;border-bottom-right-radius:20px;border-bottom-left-radius:20px}article{background-color:whitesmoke;padding:5px}span{font-size:9px}label{display:block;margin-top:10px}button{margin-top:5px}form{padding:2% 40%;background-color:beige;border:red solid;border-bottom-right-radius:190px}footer{background-color:#097293;margin-top:5px;text-align:center;border-bottom-left-radius:35px;border-bottom-right-radius:15px;color:white;padding:5px}aside{display:block;width:15%;border:solid 2px black;padding:40px;border-bottom-left-radius:30px;border-bottom-right-radius:30px;border-top-left-radius:30px;border-top-right-radius:30px}.muestrario{display:block;float:right;margin-right:30%;margin-top:5%}.progressbar{-moz-orient:vertical;display:inline}label{background-color:green;padding:10px;border:2px black solid;color:white}.container{width:400px;height:200px;position:relative;top:30%;left:50%;overflow:hidden;text-align:center;transform:translate(-50%,-50%)}.GaugeMeter{position:Relative;text-align:Center;overflow:Hidden;cursor:Default;display:inline-block}.GaugeMeter SPAN,.GaugeMeter B{width:54%;position:Absolute;text-align:Center;display:Inline-Block;color:RGBa(0,0,0,.8);font-weight:100;font-family:'Open Sans',Arial;overflow:Hidden;white-space:NoWrap;text-overflow:Ellipsis;margin:0 23%}.GaugeMeter[data-style='Semi'] B{width:80%;margin:0 10%}.GaugeMeter S,.GaugeMeter U{text-decoration:None;font-size:.60em;font-weight:200;opacity:.6}.GaugeMeter B{color:#000;font-weight:200;opacity:.8}.representaciones{padding-left:30%;padding-top:10%;padding-bottom:30%}</style>";
  weblecturas =weblecturas+"</head> <body> <header> <h1>Estacion meteorologica</h1> </header> <nav>";
  weblecturas =weblecturas+"<a href>Inicio</a> <a href=/lecturas>Configuracion</a> <a href=/control>Control</a> <a href=/about>Sobre el autor</a> </nav>"; 
  weblecturas =weblecturas+"<section id=contenido> <center><h2>Lecturas</h2></center> <article> <h3>Estación meteorologica con ESP3266</h3>";
  weblecturas =weblecturas+"<span>Estacion meteorologica de <a href=http://www.trastejant.com>Trastejant</a></span> <p>Información de los sensores conectados a mi NodeMCU.</p>"; 
  weblecturas =weblecturas+"<label>Temperatura:</label>"+String(temperature)+"<label>Presion:</label>"+String(event.pressure)+"<label>Luminosidad</label>"+String(luxometro.readLightLevel())+"</section>";
  weblecturas =weblecturas+"<footer>CrakerNano <a href=http://www.Trastejant.es</a></footer> </body> </html>";
  
  //String weblecturas;
  server.send(200, "html",weblecturas);
}

void setup(void) {
  Serial.begin(115200);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);



  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    Serial.print ( "." );

  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  Serial.println("\nPrueba del sensor de presión");
  Serial.println("");
  if (!bmp.begin()) { // Initicializa el sensor
    // Error en la detección del sensor
    Serial.print("Ooops, BMP085 no detectado ... Comprueba las conexiones!");
    while (1); // Bucle infinito
  }
    displaySensorDetails();
    luxometro.begin(luxMode); // Inicializar BH1750


  //Configuracion de la navegacion
  server.on("/", datos);

  //Inicializacion del servidor web
  server.begin();
  Serial.println ( "HTTP server started" );
  //--------------------------- push inicial --------------------//
  sensors_event_t event;
  bmp.getEvent(&event);              
  bmp.getTemperature(&temperature);
  uint16_t lux = luxometro.readLightLevel(); // Lectura del BH1750
  if(saveData(id, event.pressure,lux, temperature, sensor.readHumidity())){
    Serial.println("Almacenado correctamente");    
  }else{
    Serial.println("Fallo al subir los datos");
  }
  
}

void loop() {

     
    if ((millis() - previousMillis) >= frecuencia){
      previousMillis = millis();
    
      // Obtiene un nuevo evento del sensor      
      sensors_event_t event;
      bmp.getEvent(&event);              
      bmp.getTemperature(&temperature);
      uint16_t lux = luxometro.readLightLevel(); // Lectura del BH1750
      
      if(saveData(id, event.pressure,lux, temperature, sensor.readHumidity())){
       Serial.println("Almacenado correctamente");    
      }else{
         Serial.println("Fallo al subir los datos");
      }
      
    }  

    server.handleClient();
} 
