#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <Time.h>//EVITAR LLAMAR A TIME AQUI
#include "NTP.h"

IPAddress timeServer(129, 6, 15, 28); // time.nist.gov NTP server

//instanciamos un objeto de la libreria udp
WiFiUDP udp;
unsigned int localPort = 2390;

NTP::NTP() {}

/**
 * Inicializacion de la libreria. Se pone a la escucha por defecto en el puerto 2390.
 */

void NTP::begin() {udp.begin(localPort);}


/**
*Inicializa la libreria escuchando en el puerto indicado
*/
void NTP::begin(int port) {udp.begin(port);}

/**
*Gestiona el envio de paquetes
*/

unsigned long NTP::sendNTPpacket(IPAddress& address) {
  

  //Inicializamos el buffer a 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  
  // Inicializamos los valores del NTP request 
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12]  = 49;
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;

  udp.beginPacket(address, 123); //NTP requests are to port 123
  udp.write(packetBuffer, NTP_PACKET_SIZE);
  udp.endPacket();
}

/**
* Devuelve el tiempo en hora unix
*/

unsigned long NTP::get_unix_time() {
  WiFi.hostByName(ntpServerName, timeServerIP);//Obtenemos la dirección del host.
  
  sendNTPpacket(timeServerIP); //Enviamos la solicitud al servidor NTP
  
  //Esperamos a la respuesta
  delay(1000);

  //Nos aseguramos de haber obtenido respuesta
  int cb = udp.parsePacket();
  if (!cb) {
    return -1;
  }
  else {
    //Si hemos recibido los paquetes empezamos a trabajar con ellos.
    udp.read(packetBuffer, NTP_PACKET_SIZE); //leemos el paquete dentro del buffer

    //El servido contesta con dos palabras de 4bytes, las extraemos.
    unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
    unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);

    //Combinamos ambas palabras en una sola para obtener el tiempo NTP (segundos transcurridos desde 1/1/1900)
    
    unsigned long secsSince1900 = highWord << 16 | lowWord;

    return secsSince1900;
  }
}

/**
*Devuelve la hora actual
*/
unsigned long NTP::get_hour() { 
    //Obtenemos y devolvemos la hora
    return ((onTime() % 86400L) / 3600);
  }




/**
 * Devuelve el minuto actual
 */
unsigned long NTP::get_minutes() {
    //obtenemos y devolvemos los minutos
    return ((onTime()  % 3600) / 60);
}

/**
*Devuelve el segundo actual
*/

unsigned long NTP::get_secons() {
    //Obtenemos y devolvemos los segundos
    return (onTime() % 60); // print the second 
}

/**
*Devuelve la hora actual
*/
unsigned long NTP::get_hour(int epoch) { 
    //Obtenemos y devolvemos la hora
    return ((epoch % 86400L) / 3600);
  }




/**
 * Devuelve el minuto actual
 */
unsigned long NTP::get_minutes(int epoch) {
    //obtenemos y devolvemos los minutos
    return ((epoch  % 3600) / 60);
}

/**
*Devuelve el segundo actual
*/

unsigned long NTP::get_secons(int epoch) {
    //Obtenemos y devolvemos los segundos
    return (epoch % 60); // print the second 
}

/**
*Devuelve la hora como un String en formato HH:MM:SS
*/
String NTP::get_timeNow() {
  WiFi.hostByName(ntpServerName, timeServerIP);
  String timeNow;
  sendNTPpacket(timeServerIP); 
  delay(1000);

  int cb = udp.parsePacket();
  if (!cb) {
    return "-1";
  }
  else {

    
    udp.read(packetBuffer, NTP_PACKET_SIZE);    

    unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
    unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);
 
    unsigned long secsSince1900 = highWord << 16 | lowWord;
    
    const unsigned long seventyYears = 2208988800UL;

    unsigned long epoch = secsSince1900 - seventyYears;

    timeNow = ((epoch % 86400L) / 3600); 
    timeNow = timeNow + ':';

    if ( ((epoch % 3600) / 60) < 10 ) {
      //si han pasado menos de 10 añadimos un 0
      timeNow = timeNow + '0';
    }


    timeNow = timeNow + ((epoch % 3600) / 60); 
    timeNow = timeNow + ":";
    if ( (epoch % 60) < 10 ) {
    
      timeNow = timeNow + '0';
    }
    timeNow = timeNow + epoch % 60; 
  }
  return timeNow;
}

/**
 * Devuelve la hora como un String con formato HH:MM:SS en el uso horario indicado
 */
String NTP::get_timeNow(int UTC) {
  WiFi.hostByName(ntpServerName, timeServerIP);
  String timeNow;
  sendNTPpacket(timeServerIP);   
  delay(1000);

  int cb = udp.parsePacket();
  if (!cb) {
    return "-1";
  }
  else {

    
    udp.read(packetBuffer, NTP_PACKET_SIZE);

    

    unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
    unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);
    
    unsigned long secsSince1900 = highWord << 16 | lowWord;

   
    const unsigned long seventyYears = 2208988800UL;
    
    unsigned long epoch = secsSince1900 - seventyYears;

    timeNow = ((epoch % 86400L) / 3600) + UTC;
    timeNow = timeNow + ':';

    if ( ((epoch % 3600) / 60) < 10 ) {
      
      timeNow = timeNow + '0';
    }


    timeNow = timeNow + ((epoch % 3600) / 60); 
    timeNow = timeNow + ":";
    if ( (epoch % 60) < 10 ) {     
      timeNow = timeNow + '0';
    }
    timeNow = timeNow + epoch % 60; 
  }
  return timeNow;
}

time_t NTP::toTime( int dia, int mes, int anyo, int hora, int minuto, int segundo){   
       tmElements_t Fecha ;   // Estructura para time
       Fecha.Second = segundo;
       Fecha.Minute = minuto ;
       Fecha.Hour = hora ;
       Fecha.Day =  dia ;
       Fecha.Month = mes ;
       Fecha.Year = anyo -1970 ;

       return makeTime(Fecha) ;
   }

int NTP::get_year() {
  // TIENE QUE CALCULAR EL ANYO POR SI MISMA!!
  
  WiFi.hostByName(ntpServerName, timeServerIP);
  String timeNow;
  sendNTPpacket(timeServerIP);   
  delay(1000);

  int cb = udp.parsePacket();
  if (!cb) {
    return -1;
  }
  else {

    
    udp.read(packetBuffer, NTP_PACKET_SIZE);

    

    unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
    unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);
    
    unsigned long secsSince1900 = highWord << 16 | lowWord;

   
    const unsigned long seventyYears = 2208988800UL;
    unsigned long epoch = secsSince1900 - seventyYears;
    return epoch;
    //return year();    
  }
}

 int NTP::get_month() {
  //MEJORAR
    return month();
  }


 int NTP::get_day() {
  // MEJORAR
    return day();
  }


 int NTP::onTime(){

  //OPTIMIZAR.
  WiFi.hostByName(ntpServerName, timeServerIP);
  String timeNow;
  sendNTPpacket(timeServerIP);   
  delay(1000);

  int cb = udp.parsePacket();
  if (!cb) {
    return -1;
  }else {

    
    udp.read(packetBuffer, NTP_PACKET_SIZE);

    

    unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
    unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);
    
    unsigned long secsSince1900 = highWord << 16 | lowWord;

   
    const unsigned long seventyYears = 2208988800UL;
    unsigned long epoch = secsSince1900 - seventyYears;
    setTime(epoch);//Devolver el tiempo y calcularlo con funciones dia/mes/anyo
    return epoch; 
  }
 }

 int NTP::ajusteHorario( int dia, int mes, int anyo, int hora, int minuto, int segundo){   
  int ajuste;     
  time_t cambio_1, cambio_2, fecha_hoy;

  for (int i = 31 ; i >0 ; i--){
    cambio_1 = toTime(i, 3, 2015, 2, 0, 0) ; // A las 2 am seran las 3
        if ( weekday( cambio_1) == 1 )    // Domingo = 1
        break ;
   }

   for (int i = 31 ; i >0 ; i--){
    cambio_2 = toTime(i, 10, 2015, 3, 0, 0) ; // A las 3 am seran las 2
      if ( weekday( cambio_2) == 1 )    // Domingo = 1
      break;    
   }

   fecha_hoy = toTime(dia, mes, anyo, hora, minuto, segundo);
   if ( fecha_hoy > cambio_1 && fecha_hoy < cambio_2){
     ajuste = 2;
   }else{
     ajuste = 1; 
   }

   return ajuste;
 }

   
