#define btn_ok D5
#define btn_up D6
#define btn_down D7
#define num_menu_item 7

int pulsado = 0; 
int estado = 0;
int volatile posicion = 1;

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

void initMenu(){
    pinMode(btn_up, INPUT_PULLUP);
    pinMode(btn_ok, INPUT_PULLUP);
    pinMode(btn_down, INPUT_PULLUP);
    
    attachInterrupt(btn_ok,showMenu,FALLING);
    attachInterrupt(btn_up,up_menu,FALLING);
    attachInterrupt(btn_down,down_menu,FALLING);
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

