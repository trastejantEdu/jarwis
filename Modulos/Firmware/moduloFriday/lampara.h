#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#if defined (__AVR_ATtiny85__)
   if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif

#define PIN D3
#define NUMPIXELS 4


Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

String R,G,B;
int Ri, Gi, Bi;

String intensidad;
int Ii;

void rgb_begin(){
   Serial.println("INICIALIZADA LIBRERIA NEOPIXEL");
   pixels.begin();
   pixels.setPixelColor(1, (0, 255, 255)); //full-bright cyan
   pixels.show();
   delay(250);
   pixels.setPixelColor(1, (0, 0, 0)); //full-bright cyan
   pixels.show();
   
}


void iluminacion(int R, int G, int B, int I){
   for(int i=0;i<NUMPIXELS;i++){   
    pixels.setPixelColor(i, pixels.Color(R,G,B));
    pixels.setBrightness(I);
    pixels.show(); 
    delay(200);
  }
}
