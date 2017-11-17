#include "SSD1306.h"

#define btn_ok D5
#define btn_up D6
#define btn_down D7
#define num_menu_item 7

int pulsado = 0; 
int estado = 0;
int volatile posicion = 1;

//SSD1306  display(0x3c, D1, D2);

enum pos_menu {
  opc1 = 20,
  opc2 = 30,
  opc3 = 40
};

int selector(int pos){
  switch (pos) {
    case 0:    // your hand is on the sensor
      //principal();
      break;
    case 1:    // your hand is close to the sensor
      return 20;
      break;
    case 2:    // your hand is a few inches from the sensor
      return 30;
      break;
    case 3:    // your hand is nowhere near the sensor
      return 40;
      break;

    case 4:    // your hand is nowhere near the sensor
      return 50;
      break;

    case 5:    // your hand is nowhere near the sensor
      return 20;
      break;

    case 6:    // your hand is nowhere near the sensor
      return 30;
      break;

    case 7:    // your hand is nowhere near the sensor
      return 40;
      break;
  }
}

void reset(int eleccion){
  if(eleccion==0){
    Serial.println("No registrar");
  }else if(eleccion ==1){
    ESP.reset();
  }
  
}

void reiniciar(){
  Serial.println("reiniciar");
   int eleccion = 0;
   int salir = 0;
   delay(200);//Espera para evitar el robote del intro
   
   while(salir!=1){
    
     display.clear();
     display.setTextAlignment(TEXT_ALIGN_CENTER);
     display.setFont(ArialMT_Plain_10);
     display.drawString(60, 0, "Registrar Datos en BBDD");
     display.drawHorizontalLine(5, 12, 110);
       
     display.setFont(ArialMT_Plain_10);   
     display.drawString(30, 25, "SI");  
     display.drawString(60, 25, "NO");  
         
     if(eleccion == 1){
      display.drawRect(23, 25,15,15);
     }

     if(eleccion == 0){
      display.drawRect(53, 25,15,15);
     }
     
     display.display();
       
     if(digitalRead(btn_up)==LOW){eleccion=0;}
     if(digitalRead(btn_down)==LOW){eleccion=1;}
     if(digitalRead(btn_ok)==LOW){salir=1;}
     
     Serial.println(eleccion);     
     
   }

  reset(eleccion);
  
  
  interrupts();
}

void  enableDatalogger(int eleccion){
  if(eleccion==0){
    Serial.println("No registrar");
  }else if(eleccion ==1){
    Serial.println("Registrar");
  }
}

void  enableWifi(int eleccion){
  if(eleccion==0){
    Serial.println("WiFi Off");
  }else if(eleccion ==1){
    Serial.println("WiFi ON");
  }
}

void enableAlarm(int horas, int minutos){
  
}

/**
 * Activar o desactivar el registro de datos en la base de datos.
 */

void registrarDatos(){
  Serial.println("registrar Datos");
   int eleccion = 0;
   int salir = 0;
   delay(200);//Espera para evitar el robote del intro
   
   while(salir!=1){
    
     display.clear();
     display.setTextAlignment(TEXT_ALIGN_CENTER);
     display.setFont(ArialMT_Plain_10);
     display.drawString(60, 0, "Registrar Datos en BBDD");
     display.drawHorizontalLine(5, 12, 110);
       
     display.setFont(ArialMT_Plain_10);   
     display.drawString(30, 25, "SI");  
     display.drawString(60, 25, "NO");  
         
     if(eleccion == 1){
      display.drawRect(23, 25,15,15);
     }

     if(eleccion == 0){
      display.drawRect(53, 25,15,15);
     }
     
     display.display();
       
     if(digitalRead(btn_up)==LOW){eleccion=0;}
     if(digitalRead(btn_down)==LOW){eleccion=1;}
     if(digitalRead(btn_ok)==LOW){salir=1;}
     
     Serial.println(eleccion);     
     
   }

  enableDatalogger(eleccion);
  interrupts();
  
}

void actWifi(){
  Serial.println("Activar/Desactivar Wifi");
  int eleccion = 0;
   int salir = 0;
   delay(200);//Espera para evitar el robote del intro
   
   while(salir!=1){
    
     display.clear();
     display.setTextAlignment(TEXT_ALIGN_CENTER);
     display.setFont(ArialMT_Plain_10);
     display.drawString(60, 0, "WiFi");
     display.drawHorizontalLine(5, 12, 110);
       
     display.setFont(ArialMT_Plain_10);   
     display.drawString(30, 25, "SI");  
     display.drawString(60, 25, "NO");  
         
     if(eleccion == 1){
      display.drawRect(23, 25,15,15);
     }

     if(eleccion == 0){
      display.drawRect(53, 25,15,15);
     }
     
     display.display();
       
     if(digitalRead(btn_up)==LOW){eleccion=0;}
     if(digitalRead(btn_down)==LOW){eleccion=1;}
     if(digitalRead(btn_ok)==LOW){salir=1;}
     
     Serial.println(eleccion);     
     
   }

  enableWifi(eleccion);
  interrupts();
}

void alarmas(){
  Serial.println("Configurar alarmas");
  int eleccion = 0;
  int salir = 0;
  int minutos = 00;
  int horas = 00;
   delay(200);//Espera para evitar el robote del intro
   
   while(salir!=1){
    
     display.clear();
     display.setTextAlignment(TEXT_ALIGN_CENTER);
     display.setFont(ArialMT_Plain_10);
     display.drawString(60, 0, "Configurar alarma");
     display.drawHorizontalLine(5, 12, 110);
       
     display.setFont(ArialMT_Plain_10);   
     display.drawString(30, 25, String(horas));  
     display.drawString(33, 25, ":");
     display.drawString(60, 25, String(minutos));  
         
     if(eleccion == 1){
      display.drawRect(23, 25,15,15);
     }

     if(eleccion == 0){
      display.drawRect(53, 25,15,15);
     }
     
     display.display();
       
     if(digitalRead(btn_up)==LOW){minutos=minutos+1;}
     if(digitalRead(btn_down)==LOW){minutos = minutos-1;}
     if(digitalRead(btn_ok)==LOW){salir=1;}
     
     Serial.println(eleccion);     
     
   }

  enableAlarm(horas,minutos);
  interrupts();
  
}

void luz(){
  Serial.println("Encender/Apagar luces");
  interrupts();
}

void informacion(){
  Serial.println("ver informacion");
  interrupts();
}


void opcSelec(int opc){

    switch (opc) {
    case 0:    // your hand is on the sensor
      //principal();
      break;
    case 1:    // your hand is close to the sensor
      reiniciar();
      break;
    case 2:    // your hand is a few inches from the sensor
      registrarDatos();
      break;
    case 3:    // your hand is nowhere near the sensor
      actWifi();
      break;

    case 4:    // your hand is nowhere near the sensor
      alarmas();
      break;

    case 5:    // your hand is nowhere near the sensor
      luz();
      break;

    case 6:    // your hand is nowhere near the sensor
      informacion();
      break;

    case 7:    // your hand is nowhere near the sensor
      estado = !estado;
      break;
  }
  
}

void mostrarMenu(){   
   noInterrupts();
   Serial.println("menus");
   delay(200);
   //posicion = 1; 
   while (estado==1){
   display.clear();
   display.setTextAlignment(TEXT_ALIGN_CENTER);
   display.setFont(ArialMT_Plain_10);
   display.drawString(60, 0, "Menu");
   display.drawHorizontalLine(5, 12, 110);
   display.setFont(ArialMT_Plain_10);
   display.fillCircle(5,selector(posicion),2);
   
   if(posicion<5){
     display.drawString(30, 12, "Reinciar");   
     display.drawString(45, 25, "Registrar datos");
     display.drawString(20, 35, "Wifi");
     display.drawString(30, 45, "Alarma");
   }else if(posicion>4){
     display.drawString(20, 12, "Luz");
     display.drawString(40, 25, "Informacion");
     display.drawString(20, 35, "Salir");
   }
   
   display.display();
   
   if(posicion>num_menu_item){
    posicion = 1;
   }
  delay(10);
  
  Serial.println(posicion);
  
  if(digitalRead(btn_ok)==LOW){
    opcSelec(posicion);
  }
 }
}

/*
void principal(){
   display.clear();
   display.setTextAlignment(TEXT_ALIGN_CENTER);
   display.setFont(ArialMT_Plain_16);
   display.drawString(60, 0, "HOLA");
   display.drawHorizontalLine(5, 17, 110);
   display.drawString(60, 40, String(posicion));
   display.display();
   delay(500);
}
*/
void showMenu(){
  //mostrarMenu();
  estado = !estado;
}


void up_menu(){
  if(posicion<num_menu_item){posicion = posicion+1;}
}

void down_menu(){
  if(posicion>1){posicion = posicion-1;}
}

void initMenus() {
  // put your setup code here, to run once:
  /*
    display.init();
    display.clear();

    Serial.begin(115200);
*/
    pinMode(btn_up, INPUT_PULLUP);
    pinMode(btn_ok, INPUT_PULLUP);
    pinMode(btn_down, INPUT_PULLUP);
    
    attachInterrupt(btn_ok,showMenu,FALLING);
    attachInterrupt(btn_up,up_menu,FALLING);
    attachInterrupt(btn_down,down_menu,FALLING);
    Serial.println("Menus activos");
}

/*
void loop() {
  // put your main code here, to run repeatedly:


 if(estado==1){
  mostrarMenu();
 }else{
  principal();
 }

}
*/





