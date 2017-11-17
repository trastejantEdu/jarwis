/* 
 *  bool conexionWiFi(const char* ssid,const char* password){
int progress;
 
   WiFi.begin(ssid,password);
  //Cambiar por un bucle NO bloequante  
  while ( WiFi.status() != WL_CONNECTED ) {
    progress= progress + 20;
    delay ( 500 );
    Serial.print ( "." );
    //display.print(".");
    if(progress>=100) progress=0;
    display.drawProgressBar(0, 0, 120, 10, progress);
    display.display();
  }

 Serial.println ( "" );
 Serial.print ( "Connected to " );
 Serial.println ( ssid );
 Serial.print ( "IP address: " );
 Serial.println ( WiFi.localIP() );
 return true;
}
*/

#include <EEPROM.h>

//-------------------VARIABLES GLOBALES--------------------------
int contconexion = 0;
unsigned long previousMillis = 0;

char ssid[50];      
char pass[50];

const char *ssidConf = "tutorial";
const char *passConf = "12345678";

String mensaje = "";

//-----------CODIGO HTML PAGINA DE CONFIGURACION---------------
String pagina = "<!DOCTYPE html>"
"<html>"
"<head>"
"<title>Tutorial Eeprom</title>"
"<meta charset='UTF-8'>"
"</head>"
"<body>"
"</form>"
"<form action='guardar_conf' method='get'>"
"SSID:<br><br>"
"<input class='input1' name='ssid' type='text'><br>"
"PASSWORD:<br><br>"
"<input class='input1' name='pass' type='password'><br><br>"
"<input class='boton' type='submit' value='GUARDAR'/><br><br>"
"</form>"
"<a href='escanear'><button class='boton'>ESCANEAR</button></a><br><br>";

String paginafin = "</body>"
"</html>";

//-------------------PAGINA DE CONFIGURACION--------------------
void paginaconf() {
  server.send(200, "text/html", pagina + mensaje + paginafin); 
}

//----------------Función para grabar en la EEPROM-------------------
void grabar(int addr, String a) {
  int tamano = a.length(); 
  char inchar[50]; 
  a.toCharArray(inchar, tamano+1);
  for (int i = 0; i < tamano; i++) {
    EEPROM.write(addr+i, inchar[i]);
  }
  for (int i = tamano; i < 50; i++) {
    EEPROM.write(addr+i, 255);
  }
  EEPROM.commit();
}

//---------------------------ESCANEAR----------------------------
void escanear() {  
  int n = WiFi.scanNetworks(); //devuelve el número de redes encontradas
  Serial.println("escaneo terminado");
  if (n == 0) { //si no encuentra ninguna red
    Serial.println("no se encontraron redes");
    mensaje = "no se encontraron redes";
  }  
  else
  {
    Serial.print(n);
    Serial.println(" redes encontradas");
    mensaje = "";
    for (int i = 0; i < n; ++i)
    {
      // agrega al STRING "mensaje" la información de las redes encontradas 
      mensaje = (mensaje) + "<p>" + String(i + 1) + ": " + WiFi.SSID(i) + " (" + WiFi.RSSI(i) + ") Ch: " + WiFi.channel(i) + " Enc: " + WiFi.encryptionType(i) + " </p>\r\n";
      //WiFi.encryptionType 5:WEP 2:WPA/PSK 4:WPA2/PSK 7:open network 8:WPA/WPA2/PSK
      delay(10);
    }
    Serial.println(mensaje);
    paginaconf();
  }
}



//---------------------GUARDAR CONFIGURACION-------------------------
void guardar_conf() {
  
  Serial.println(server.arg("ssid"));//Recibimos los valores que envia por GET el formulario web
  grabar(0,server.arg("ssid"));
  Serial.println(server.arg("pass"));
  grabar(50,server.arg("pass"));

  mensaje = "Configuracion Guardada...";
  paginaconf();
}

//--------------------MODO_CONFIGURACION------------------------
void modoconf() {
   
  delay(100);

  WiFi.softAP(ssidConf, passConf);
  IPAddress myIP = WiFi.softAPIP(); 
  Serial.print("IP del acces point: ");
  Serial.println(myIP);
  Serial.println("WebServer iniciado...");
  confiLogo(ssidConf,passConf,myIP.toString());
  server.on("/", paginaconf); //esta es la pagina de configuracion

  server.on("/guardar_conf", guardar_conf); //Graba en la eeprom la configuracion

  server.on("/escanear", escanear); //Escanean las redes wifi disponibles
  
  server.begin();

  while (true) {
      server.handleClient();
  }
}


//------------------------SETUP WIFI-----------------------------
void setup_wifi() {
  int progress;
// Conexión WIFI
  WiFi.mode(WIFI_STA); //para que no inicie el SoftAP en el modo normal
  WiFi.begin(ssid, pass);
  
  for(int i=0; i<20;i++){    
    progress= progress + 5;
    delay ( 200 );
    Serial.print ( "." );
    if(progress>=100) progress=0;
    display.drawProgressBar(0, 0, 120, 10, progress);
    display.display();
  }
  
if(WiFi.status() == WL_CONNECTED){
    Serial.println ( "" );
    Serial.print ( "Connected to " );
    Serial.println ( ssid );
    Serial.print ( "IP address: " );
    Serial.println ( WiFi.localIP() );
    Serial.print("Chip ID: ");
    Serial.println(ESP.getChipId());
    pantalla_info(ESP.getChipId(),ssid, WiFi.localIP().toString());
    
  }else{
    
    modoconf();
  }
}

//--------------------------------------------------------------
WiFiClient espClient;
//ESP8266WebServer server(80);
//--------------------------------------------------------------








//-----------------Función para leer la EEPROM------------------------
String leer(int addr) {
   byte lectura;
   String strlectura;
   for (int i = addr; i < addr+50; i++) {
      lectura = EEPROM.read(i);
      if (lectura != 255) {
        strlectura += (char)lectura;
      }
   }
   return strlectura;
}



//------------------------SETUP-----------------------------
bool conexionWiFi(){

 // pinMode(13, OUTPUT); // D7 
  
  // Inicia Serial
  //Serial.begin(115200);
  //Serial.println("");

  EEPROM.begin(512);

  leer(0).toCharArray(ssid, 50);
  leer(50).toCharArray(pass, 50);
  Serial.println(ssid);
  Serial.println(pass);

  setup_wifi();
  delay(500);
  return true;
  //if(WiFi.status() == WL_CONNECTED){return true;}else{return false;}
}

