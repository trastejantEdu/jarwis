#include <ESP8266HTTPClient.h>
#include "conf.h"

bool saveData(const int id, float presion,uint16_t lux, float temperatura, float humedad){
  if((WiFi.status() == WL_CONNECTED)) {
        //cast de datos
        //String humedadNow = String(humedad); 
        //String temperaturaNow = String(temperatura); 
        
        HTTPClient http;

        //USE_SERIAL.print("[HTTP] begin...\n");
        
        //Envia la info para ser almacenada en el servidor
        url = url += id;
        url = url += "&temperatura=";
        url = url += temperatura;
        url = url += "&humedad=";
        url = url += humedad;
        url = url += "&presion=";
        url = url += presion;
        url = url += "&luz=";
        url = url += lux;
        
        http.begin(url);

        //Respuesta del servidor (¡¡IMPLEMENTAR SISTEMA DE COMPROBACIÓN!!)
        //USE_SERIAL.print("[HTTP] GET...\n");
      
        int httpCode = http.GET();

        // httpCode will be negative on error
        if(httpCode > 0) {
            // HTTP header has been send and Server response header has been handled
            //USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);

            // file found at server
            if(httpCode == HTTP_CODE_OK) {
                String payload = http.getString();
                //USE_SERIAL.println(payload);
            }
            return true;
        } else {
            //USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
          return false;
        }
        //Cierra la conexion
        http.end();
        
    }else{return false;}
}

