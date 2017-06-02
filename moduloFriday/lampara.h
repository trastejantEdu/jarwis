#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#if defined (__AVR_ATtiny85__)
   if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif

#define PIN 4
#define NUMPIXELS 16

String R,G,B;
int Ri, Gi, Bi;

String intensidad;
int Ii;

void rgb_begin(){
  
}


void iluminacion(int R, int G, int B, int I){
   for(int i=0;i<NUMPIXELS;i++){   
    pixels.setPixelColor(i, pixels.Color(R,G,B));
    pixels.setBrightness(I);
    pixels.show(); 
    delay(200);
  }
}
