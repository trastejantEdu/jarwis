#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define rele 13//D7
#define btn 14//D5

const char* ssid = "YOURSSID";
const char* password = "YOURPASSWORD";

const char* www_username = "jarvis";
const char* www_password = "1234";

int estado = 0;
IPAddress moduleIP;

ESP8266WebServer server(80);

void pagConf(){
  
}

void miWeb(void) { 
  String web = "<!DOCTYPE HTML><html><head><title>Interruptor WiFi · JARVIS </title><meta charset='utf-8'><meta name='viewport' content='width=device-width, initial-scale=1'><link rel='stylesheet' href='https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css'><script src='https://ajax.googleapis.com/ajax/libs/jquery/3.2.0/jquery.min.js'></script><script src='https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js'></script></head><body><div class='container'><header><h1>Jarvis Control</h1><h1>Modulo interruptor.</h2></header><form action='/'>";
  web = web + "<input type='submit' value='1' name='led'/>";
  if(!estado){
    web = web + "<button type='button' class='btn btn-danger'>Apagado</button>";
  }else{
    web = web + "<button type='button' class='btn btn-success active'>Encendido</button>";
  }
  web = web +"</form></div><footer>"+moduleIP+"</footer></body></html>";

  server.send(200, "html",web);  
  
  server.method() == HTTP_GET;  

  String estatus = server.arg(0);
  int stat = estatus.toInt();

  if(stat == 1){
    digitalWrite(rele,estado);
    estado = !estado;
  }else{
    digitalWrite(rele,LOW);    
  }
  
  delay(1);
}

void pagError(){
  String message = "No tengo esa web :-(\n\n";
  message += "URI: ";
  message += server.uri();


  server.send ( 404, "text/plain", message );
}

void showMenu(){
  noInterrupts();
  digitalWrite(rele,estado);
  estado = !estado;
  delay(100);
  interrupts();
}

void setup(void){
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
  moduleIP = WiFi.localIP();
  Serial.println(moduleIP);
  Serial.print("Intensidad:");
  Serial.println(WiFi.RSSI());

  pinMode(rele,OUTPUT);
  digitalWrite(rele,estado);

  pinMode(btn, INPUT_PULLUP);
  attachInterrupt(btn,showMenu,FALLING);

  server.on("/", miWeb);
  server.on("/conf", pagConf);
  server.onNotFound (pagError);

  server.on("/automode", [](){
    if(!server.authenticate(www_username, www_password)){
      return server.requestAuthentication();
    }else{
     digitalWrite(rele,estado);
     estado = !estado;      
     String msg = "Ok ->"+estado;
     server.send(200, "text/plain", msg);
      
    }
  });

  
  server.begin();
  Serial.println("HTTP server started");
}

void loop(){
  server.handleClient();
}
