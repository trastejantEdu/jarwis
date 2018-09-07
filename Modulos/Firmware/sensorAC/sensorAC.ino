/*
#define led1 D3
#define led2 2
#define buzzer D5
#define sensor D8
*/
/*
#define led1 8
#define led2 2
#define buzzer 7
#define sensor 9
*/
 
//Attiny
#define led1 2
#define buzzer 1
#define sensor 4

int estado = 1;

// Notes
const int Note_C  = 239;
const int Note_CS = 225;
const int Note_D  = 213;
const int Note_DS = 201;
const int Note_E  = 190;
const int Note_F  = 179;
const int Note_FS = 169;
const int Note_G  = 159;
const int Note_GS = 150;
const int Note_A  = 142;
const int Note_AS = 134;
const int Note_B  = 127;

void TinyTone(unsigned char divisor, unsigned char octave, unsigned long duration)
{
  //TCCR1 = 0x90 | (8-octave); // for 1MHz clock
  TCCR1 = 0x90 | (11-octave); // for 8MHz clock
  OCR1C = divisor-1;         // set the OCR
  delay(duration);
  TCCR1 = 0x90;              // stop the counter
}

void tinyAcusticAlarm(){
 TinyTone(Note_C, 4, 500);
 TinyTone(Note_D, 4, 500);
 TinyTone(Note_E, 4, 500);
 TinyTone(Note_F, 4, 500);
 TinyTone(Note_G, 4, 500);
 TinyTone(Note_A, 4, 500);
 TinyTone(Note_B, 4, 500);
 TinyTone(Note_C, 5, 500);
}

const int Clock = ((F_CPU/1000000UL) == 16) ? 4 : ((F_CPU/1000000UL) == 8) ? 3 : 0;
const uint8_t scale[] PROGMEM = {239,226,213,201,190,179,169,160,151,142,134,127};

void note (int n, int octave) {
  int prescaler = 8 + Clock - (octave + n/12);
  if (prescaler<1 || prescaler>15 || octave==0) prescaler = 0;
  DDRB = (DDRB & ~(1<<buzzer)) | (prescaler != 0)<<buzzer;
  OCR1C = pgm_read_byte(&scale[n % 12]) - 1;
  GTCCR = (buzzer == 4)<<COM1B0;
  TCCR1 = 1<<CTC1 | (buzzer == 1)<<COM1A0 | prescaler<<CS10;
}

void tinyVisualAlarm(){
  digitalWrite(led1, estado);
  estado=!estado;
}

void visualAlarm(){
  for (int fadeValue = 0 ; fadeValue <= 255; fadeValue += 5) {
    // sets the value (range from 0 to 255):
    analogWrite(led1, fadeValue);
    // wait for 30 milliseconds to see the dimming effect
    delay(30);
  }

  // fade out from max to min in increments of 5 points:
  for (int fadeValue = 255 ; fadeValue >= 0; fadeValue -= 5) {
    // sets the value (range from 0 to 255):
    analogWrite(led1, fadeValue);
    // wait for 30 milliseconds to see the dimming effect
    delay(30);
  }
}

void acusticAlarm(){
  digitalWrite(led1,HIGH);
    // turn off tone function for pin 8:
  noTone(buzzer);
  // play a note on pin 6 for 200 ms:
  tone(buzzer, 440, 200);
  delay(200);

  // turn off tone function for pin 6:
  noTone(buzzer);
  // play a note on pin 7 for 500 ms:
  tone(buzzer, 494, 500);
  delay(500);

  // turn off tone function for pin 7:
  noTone(buzzer);
  // play a note on pin 8 for 300 ms:
  tone(buzzer, 523, 300);
  delay(300);
  digitalWrite(led1,LOW);
}

void check(){
  tone(buzzer, 1000, 10);
  delay(1);
}

void setup() {
  // put your setup code here, to run once:
  check();
  //pinMode(sensor,INPUT_PULLUP);
  pinMode(sensor,INPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(led1,OUTPUT);

  digitalWrite(led1,LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(!digitalRead(sensor)){
    noTone(buzzer);
    digitalWrite(led1,LOW);
  }
  else{
    //tinyAcusticAlarm();
    note(12, 4);
    tinyVisualAlarm();
  }
   


}
