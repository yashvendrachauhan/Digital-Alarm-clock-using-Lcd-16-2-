#include <Wire.h>
#include<EEPROM.h>
#include "Sodaq_DS3231.h"
#include <LiquidCrystal.h>

LiquidCrystal lcd(1, 2, 4, 5, 6, 7);
int temp, inc, hours1, minut, add = 11;

int next = 10;
int INC = 11;
int set_mad = 12;
char weekDay[][4] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
//char Month[][4] ={ "Dec","Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov"};
byte degree[8] = {
  B00110,
  B01001,
  B01001,
  B00110,
  B00000,
  B00000,
  B00000,
  B00000
};
byte alarm[8] = {
  B00100,
  B01110,
  B01110,
  B01110,
  B11111,
  B11111,
  B00100,
  B00000
};
byte Char1[8] = {
   B00010,
  B00100,
  B01000,
  B01000,
  B01000,
  B01000,
  B00100,
  B00010
};
byte Heart1[8] = {
  B00000,
  B01010,
  B11111,
  B11111,
  B11111,
  B01110,
  B00100,
  B00000
};
byte Heart0[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};

byte Char2[8] = {
  B01000,
  B00100,
  B00010,
  B00010,
  B00010,
  B00010,
  B00100,
  B01000
};

#define buzzer 13

int HOUR, MINUT, SECOND;


void setup()
{
  Wire.begin();
  rtc.begin();
  lcd.begin(16, 2);
  pinMode(INC, INPUT);
  pinMode(next, INPUT);
  pinMode(set_mad, INPUT);
  pinMode(buzzer, OUTPUT);
  digitalWrite(next, HIGH);
  digitalWrite(set_mad, HIGH);
  digitalWrite(INC, HIGH);
  digitalWrite(buzzer, LOW);
  lcd.setCursor(0, 0);
  lcd.print("    Welcome    ");
  delay(2000);

lcd.createChar(0,degree);
lcd.createChar(1,alarm);
lcd.createChar(2,Char1);
lcd.createChar(3,Heart1);
lcd.createChar(4,Heart0);
lcd.createChar(5,Char2);
}

void loop()
{
  int temp = 0, val = 1, temp4;
  rtc.convertTemperature();  
  DateTime now = rtc.now();
  if (digitalRead(set_mad) == 0)
  {
    lcd.setCursor(0, 0);
    lcd.print("  Set Alarm  ");
    delay(2000);
    defualt();
    time();
    delay(1000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Your Alarm time ");
    lcd.setCursor(0, 1);
    lcd.print(" has been set.  ");
    delay(2000);
  }
  lcd.clear();
  lcd.setCursor(0, 0);
  if(now.hour()<10){
  lcd.print("0");
  lcd.print(HOUR = now.hour(), DEC);}
  if(now.hour()>=10){
  lcd.print(HOUR = now.hour(), DEC);}
  lcd.print(":");
  if(now.minute()<10){
  lcd.print("0");
  lcd.print(MINUT=now.minute(),DEC);}
  if(now.minute()>=10){
  lcd.print(MINUT = now.minute(), DEC);}
  lcd.print(":");
  if(now.second()<10){
  lcd.print("0");
  lcd.print(SECOND=now.second(),DEC);}
  if(now.second()>=10){
  lcd.print(SECOND = now.second(), DEC);}
  
  lcd.setCursor(9,0);
  lcd.print(weekDay[now.dayOfWeek()]);
  
  lcd.setCursor(12,0);
  lcd.write(byte(2));
  lcd.setCursor(13,0);
  lcd.write(byte(3));
  lcd.setCursor(14,0);
  lcd.write(byte(5));
  lcd.setCursor(15,0);
  lcd.write(byte(1));

  
  lcd.setCursor(0,1);
  if(now.date()<10){
    lcd.print("0");
    lcd.print(now.date(),DEC);
  }
  if(now.date()>=10){
  lcd.print(now.date(), DEC);}
  lcd.print("/");
  if(now.month()<10){
    lcd.print("0");
    lcd.print(now.month(),DEC);
  }
  if(now.month()>10){
    lcd.print(now.month(),DEC);
  }
  lcd.print("/");
  lcd.print(now.year()-2000);
  lcd.setCursor(9,1);
  lcd.print(rtc.getTemperature());
  lcd.setCursor(14,1);
  lcd.write(byte(0));
  lcd.print("C");

  
  
  match();
  delay(200);




  

}

void defualt()
{
  lcd.setCursor(0, 1);
  lcd.print(HOUR);
  lcd.print(":");
  lcd.print(MINUT);
  lcd.print(":");
  lcd.print(SECOND);
}

void time()
{
  int temp = 1, minuts = 0, hours = 0, seconds = 0;
  while (temp == 1)
  {
    if (digitalRead(INC) == 0)
    {
      HOUR++;
      if (HOUR == 24)
      {
        HOUR = 0;
      }
      while (digitalRead(INC) == 0);
    }
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Set Alarm Time ");
    //lcd.print(x);
    lcd.setCursor(0, 1);
    lcd.print(HOUR);
    lcd.print(":");
    lcd.print(MINUT);
    lcd.print(":");
    lcd.print(SECOND);
    delay(100);
    if (digitalRead(next) == 0)
    {
      hours1 = HOUR;
      EEPROM.write(add++, hours1);
      temp = 2;
      while (digitalRead(next) == 0);
    }
  }

  while (temp == 2)
  {
    if (digitalRead(INC) == 0)
    {
      MINUT++;
      if (MINUT == 60)
      {
        MINUT = 0;
      }
      while (digitalRead(INC) == 0);
    }
    // lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print(HOUR);
    lcd.print(":");
    lcd.print(MINUT);
    lcd.print(":");
    lcd.print(SECOND);
    delay(100);
    if (digitalRead(next) == 0)
    {
      minut = MINUT;
      EEPROM.write(add++, minut);
      temp = 0;
      while (digitalRead(next) == 0);
    }
  }
  delay(1000);
}

void match()
{
  int tem[17];
  for (int i = 11; i < 17; i++)
  {
    tem[i] = EEPROM.read(i);
  }
  if (HOUR == tem[11] && MINUT == tem[12])
  {
    beep();
    beep();
    beep();
    beep();
    lcd.clear();
    lcd.print("Wake Up....");
    lcd.setCursor(0, 1);
    lcd.print("Wake Up....");
    beep();
    beep();
    beep();
    beep();
  }

}
void beep()
{
  digitalWrite(buzzer, HIGH);
  delay(500);
  digitalWrite(buzzer, LOW);
  delay(500);
}

void pattern(){

  
  lcd.setCursor(13,0);
  lcd.write(byte(3));
 

  delay(250);

  lcd.setCursor(13,0);
  lcd.write(byte(4));

  

}
