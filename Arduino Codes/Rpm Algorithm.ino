#include<LiquidCrystal.h>
#define par 10
#define del 100
struct IgnitionModule{
  int pin;
  volatile unsigned int p;
  volatile unsigned int n;
  volatile unsigned int gap[5];
}IM={3,1,0};

volatile float RPM = 0;

LiquidCrystal lcd(8,9,10,11,12,13,A3,A2,A1,A0);

void showdata(){
    lcd.setCursor(0,1);
    if(RPM<10000)
        lcd.print(" ");
    if(RPM<1000)
        lcd.print(" ");
    lcd.print(RPM);
}
void getdata(){
  if(IM.p != 0){
      RPM = (par*60000)/(IM.gap[IM.p]-IM.gap[IM.p-1]);
  }
  else{
      RPM = (par*60000)/(IM.gap[IM.p]-IM.gap[4]);
  }
  RPM *= (0.000004331*RPM + 0.9998); // Correction Factor calculated from trendline of data collected
}
void sparkdone(){
  ++IM.n%=par;
  if(IM.n == 0){
    IM.gap[IM.p] = millis();
    getdata();
    ++IM.p%=5;
  }
}
void setup() {
  pinMode(IM.pin,INPUT);
  attachInterrupt(digitalPinToInterrupt(IM.pin),sparkdone,RISING);
  lcd.begin(16,2);
  lcdInitialize();
  IM.gap[0] = 0;
}
void lcdInitialize(){
  lcd.setCursor(9,1);
  lcd.print("RPM");
}
void loop() {
  delay(del);
  showdata();
}
