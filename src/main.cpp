#include <Arduino.h>
// CD 4511 pins bind
#define LT 7
#define BI 8
#define LE 9
#define D0 11
#define D1 5
#define D2 6
#define D3 10
// Displays
#define P1 3
#define P2 2
#define P3 4
#define PERIOD 8
#define TON 3
#define TOFF 3
//buzzer
#define BUZZER 12
uint8_t pins[] = {LT, BI, LE, D0, D1, D2, D3,P1, P2, P3, BUZZER};

void writeDigit(uint8_t digit,uint8_t display);
void displayNumber(uint8_t i, uint16_t number);

void setup() {
  for(uint8_t pin: pins) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
  }
  digitalWrite(LT, HIGH);
  digitalWrite(BI, HIGH);
}

uint8_t i = 0,finish = 0;
uint16_t initialNumber = 20; // Initial number to display
uint16_t number;
uint16_t lastNumber = initialNumber;

unsigned long timebuzzeron = 0;
void loop() {
   if(!finish){
    if(millis() - timebuzzeron > 100) { // Turn off buzzer after .1 second
    digitalWrite(BUZZER, LOW);
    }
    
    number = initialNumber - millis() / 1000;

  
    if(number < lastNumber){
      lastNumber = number;
      digitalWrite(BUZZER, HIGH); // Turn on buzzer
      timebuzzeron = millis();
    }
  }
  else {
    if(millis() - timebuzzeron > 100){
      digitalWrite(BUZZER, HIGH);

    }
    if(millis() - timebuzzeron > 200) {
      digitalWrite(BUZZER, LOW);
      timebuzzeron = millis();
    }
  }

  if(number <= 0) {
    number = 000;
    finish = 1;
  }

 
  
  displayNumber(i,number);
 
  delay(TOFF); 
  
  i++;
  if(i > 2) {
    i = 0;
  }
}

void displayNumber(uint8_t i, uint16_t number){
    uint8_t unit = number % 10; // Get unit digit
    uint8_t dec = (number / 10) % 10; // Get tens digit
    uint8_t cent = (number / 100) % 10; // Get

    i == 0? writeDigit(unit,P1) : digitalWrite(P1,LOW);
    i == 1? writeDigit(dec,P2) : digitalWrite(P2,LOW);
    i == 2? writeDigit(cent,P3) : digitalWrite(P3,LOW);
}

void writeDigit(uint8_t digit,uint8_t display) {
  digitalWrite(D0, digit & 0x01);
  digitalWrite(D1, (digit >> 1) & 0x01);
  digitalWrite(D2, (digit >> 2) & 0x01);
  digitalWrite(D3, (digit >> 3) & 0x01);
  digitalWrite(display, HIGH);
  delay(TON);
  digitalWrite(display, LOW);
}