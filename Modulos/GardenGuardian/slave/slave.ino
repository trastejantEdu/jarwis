#include <TinyWire.h>

/**
 * 
 * 
 * Pinout 
 * 
 * 1  Rst NC
 * 2  A3  Sensor de humedad en tierra
 * 3  A2  LDR
 * 4 GND  Salida del MOSFET
 * 5 D0   SDA 
 * 6 D1   433Mhz
 * 7 D2   SCL
 * 8 Vcc  +3.3V
 * 
 */

    void setup(){

      TinyWire.begin(1);
      TinyWire.onReceive(requestEvent);
    }
    
    void loop(){
      digitalWrite(3,HIGH);
      delay(500);
      digitalWrite(3,LOW);
      delay(500);
    }

    
    void requestEvent(){
      String mensaje = "Hola maestro";
      //TinyWire.write("Hola maestro");   // Responde a la petición del maestro de enviarle 12 bytes
      for(int i = 0;i<mensaje.length();i++){
        TinyWire.send(mensaje.charAt(i)); 
      }
    }

