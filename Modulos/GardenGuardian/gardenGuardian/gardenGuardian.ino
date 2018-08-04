#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Wire.h>                // Incluimos la librería de comunicación I2C

const char* ssid = "MiFibra-6FD8";
const char* password = "anjx3Z3c";

ESP8266WebServer server(80);

#define D5 3
#define D6 1



String lecturas(){
  digitalWrite(D5,HIGH);//Activamos el attiny85 y los sensores
  delay(500); //Damos un tiempo para que todo se inicialice correctamente
  String lectura ="";
  Wire.requestFrom(1, 12);  // Manda una petición al esclavo numero 1 de 12 bytes
  while(Wire.available()){
    //char Datos = Wire.read(); // Leemos un byte y lo pasamos a una variable de tipo char    
    //lectura=lectura+Datos;
    lectura+=(char)Wire.read();
  }
  digitalWrite(D5,LOW);//Desconectamos todo hasta que lo volvamos a necesitar
  return lectura;
  
}

void miWeb(void) { 
  
  String web = "<!DOCTYPE HTML><html><head><title>Control con Botones</title></head><body>";
  web = web + "<form action=\"\">";
  web = web + "<input type=\"submit\" value=\"1\" name=\"led\"/>";
  web = web + "<input type=\"submit\" value=\"2\" name=\"led\"/>";
  web = web + "</form>";
  web = web + "Datos leidos: "+ lecturas();
  web = web + "</body></html>";

  server.send(200, "html",web);  
  
  server.method() == HTTP_GET;  

  String led = server.arg(0);
  int miLed = led.toInt();

  if(miLed == 1){
    digitalWrite(D5,HIGH);
  }else if(miLed == 2){
    digitalWrite(D6,HIGH);
  }else{
    digitalWrite(D5,LOW);
    digitalWrite(D6,LOW);
  }
  
  delay(1);
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  pinMode(D5,OUTPUT);
  pinMode(D6,OUTPUT);


  server.on("/", miWeb);



  server.begin();
  Serial.println("HTTP server started");
  Wire.begin();              // Iniciamos la comunicación I2C

}

void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();
}
