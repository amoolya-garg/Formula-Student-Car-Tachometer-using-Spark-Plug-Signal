#include <LiquidCrystal.h>
LiquidCrystal lcd(9, 12, 5, 4, 3, 2);

const int pin=PB5;
const uint16_t t1_load = 0;
uint16_t t1_comp=3125;
int PotPin=A0;
int PotVal;

void setup(){
  lcd.begin(16, 2);
  DDRB |= (1<<pin);
  TCCR1A=0;
  TCCR1B |= (1<<CS12);
  TCCR1B &= ~(1<<CS11);
  TCCR1B &= ~(1<<CS10);
  TCNT1 = t1_load;
  OCR1A = t1_comp;
  TIMSK1 = (1<<OCIE1A);
  sei();
}

void loop(){
  lcd.setCursor(0,0);
  lcd.print((double)(1875000/OCR1A));
  lcd.print("RPM              ");
}

ISR(TIMER1_COMPA_vect){
  PotVal = analogRead(PotPin);
  OCR1A = map(PotVal, 0, 1023, 234, 1875);
  TCNT1 = t1_load;
  PORTB ^= (1<<pin);
}
