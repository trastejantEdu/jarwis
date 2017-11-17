  #include "DHT.h"

  #define SENSORPIN D4
  #define DHTTYPE DHT22

  DHT sensor(SENSORPIN, DHTTYPE);

  bool sensorBegin(){
    sensor.begin();
    float h = sensor.readHumidity();
    float t = sensor.readTemperature();
 
    if (isnan(h) || isnan(t)) {
     Serial.println("Failed to read from DHT sensor!");
      return false;
    }else{
      Serial.println("DHT sensor OK!");
      return true;
    }
  }

  String readHumedadStr(){
  int humedad = sensor.readHumidity();
  return String(humedad);
  }

  String readTemperaturaStr(){
  int temperatura = sensor.readTemperature();
  return  String(temperatura);
  }


  float readHumedad(){
  return sensor.readHumidity();
  }

  float readTemperatura(){
  return sensor.readTemperature();
  }



