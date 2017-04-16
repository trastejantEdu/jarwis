#include "SSD1306.h"

SSD1306  display(0x3c, D1, D2);

void pantalla_info(int id, String ssid, String IP){
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
    display.drawString(15, 30, IP);
    display.drawString(0, 50, "ID:");
    display.drawString(14, 50, String(id));    
    display.drawString(90, 50, "bat");
    display.display();
  }

void pantalla_datos(String hora, int temperatura, int humedad){
  
    //cast de los datos obtenidos para motrarlos por pantalla
    String humedadNow = String(humedad); 
    String temperaturaNow = String(temperatura); 
    
    display.clear();
    display.setTextAlignment(TEXT_ALIGN_CENTER);
    display.setFont(ArialMT_Plain_24);
    display.drawString(60, 0, hora);
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_10);
    display.drawString(0, 50, "T:");
    display.drawString(10, 50, temperaturaNow);
    display.drawString(23, 50, "ºC");
    display.drawString(50, 50, "H:");
    display.drawString(60, 50, humedadNow);
    display.drawString(70, 50, "%");  
    display.display();
  
  }

void pantalla_all(String hora, String ssid,String IP, int temperatura, int humedad){
  

    //cast de los datos obtenidos para motrarlos por pantalla
    String humedadNow = String(humedad); 
    String temperaturaNow = String(temperatura); 

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
    display.drawString(15, 30, IP);

    display.drawString(0, 50, "T:");
    display.drawString(10, 50, temperaturaNow);
    display.drawString(23, 50, "ºC");
    display.drawString(50, 50, "H:");
    display.drawString(60, 50, humedadNow);
    display.drawString(70, 50, "%");
    display.drawString(90, 50, hora);
    display.display();
  }
