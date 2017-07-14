  #include "DHT.h"

  #define SENSORPIN D4
  #define DHTTYPE DHT22

  DHT sensor(SENSORPIN, DHTTYPE);



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



