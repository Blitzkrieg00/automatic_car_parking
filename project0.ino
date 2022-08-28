#include<Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F,16,2);
int trig=9;
int echo=8;
int trig0=12;
int echo0=11;
int Slot = 3;      //Enter Total number of parking Slots
int buzzer=13;
Servo myservo1;


void setup() {
  // put your setup code here, to run once:
lcd.begin();
lcd.backlight();
pinMode(trig,OUTPUT);
pinMode(echo,INPUT);
pinMode(trig0,OUTPUT);
pinMode(echo0,INPUT);
myservo1.attach(10);
lcd.setCursor (0,0);
lcd.print("   ARDUINO  ");
lcd.setCursor (0,1);
lcd.print(" PARKING SYSTEM ");
delay (2000);
lcd.clear();
}

void loop() {
myservo1.write(0);
if(calc_dis0() < 10 ){
  if(Slot>0){
      tone(buzzer,100);
      delay(500);
      noTone(buzzer);
      delay(500);
      myservo1.write(120);
      delay(2000);
      myservo1.write(0);
      Slot = Slot-1;
      delay(3000);
    }
  else{
    lcd.setCursor(0,1);
    lcd.print("Parking is full");
    delay(3000);
    lcd.clear();
  }
}

if(calc_dis() < 10 ){
  if(Slot<3){
      tone(buzzer,100);
      delay(500);
      noTone(buzzer);
      delay(500);
      myservo1.write(120);
      delay(2000);
      myservo1.write(0);
      Slot = Slot+1;
      delay(3000);
    }
  else{
    lcd.setCursor(0,1);
    lcd.print("Error");
    delay(3000);
    lcd.clear();
  }
}

lcd.setCursor (0,0);
lcd.print(" Welcome");
lcd.setCursor (0,1);
lcd.print(" Slot left: ");
lcd.println(Slot);
delay (2000);
lcd.clear();


}

//This code is written to calculate the DISTANCE using ULTRASONIC SENSOR

int calc_dis()
{
  int duration,distance;
  digitalWrite(trig,HIGH);
  delay(1000);
  digitalWrite(trig,LOW);
  duration=pulseIn(echo,HIGH);
  distance = (duration/2) / 29.1;
  Serial.println(distance);
  return distance;
}
int calc_dis0()
{
  int duration0,distance0;
  digitalWrite(trig0,HIGH);
  delay(1000);
  digitalWrite(trig0,LOW);
  duration0=pulseIn(echo0,HIGH);
  distance0 = (duration0/2) / 29.1;
  return distance0;
}
