// C++ code
//
int ledRot = 5;
int ledGruen = 3;
int ledBlau = 4;

int reglerRot = A0;
int reglerGruen = A1;
int reglerBlau = A2;

int wertRot = 0;
int wertGruen = 0;
int wertBlau = 0;

int summe = 0;
int summeNeu = 0;

String farbe = "";

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(32, 16, 2);

void setup()
{
  pinMode(ledRot, OUTPUT);
  pinMode(ledGruen, OUTPUT);
  pinMode(ledBlau, OUTPUT);
  Serial.begin(9600);
  lcd.init();
  
  lcd.setCursor(0,0);
  lcd.backlight();
  lcd.display();
}

void loop()
{
  wertRot = analogRead(reglerRot)/4;
  wertGruen = analogRead(reglerGruen)/4;
  wertBlau = analogRead(reglerBlau)/4;
  
  summeNeu = wertRot + wertGruen + wertBlau; 
  
  
  if(summe != summeNeu){   
    farbe = String(wertRot)+", "+String(wertGruen)+", "+String(wertBlau); 
    Serial.println(farbe);
    lcd.setCursor(0,0);
    lcd.print("Farbe:");
    lcd.setCursor(0,1);
    lcd.print(farbe);
    
    summe = summeNeu;
  }
  
  analogWrite(ledRot,wertRot);
  analogWrite(ledGruen,wertGruen);
  analogWrite(ledBlau,wertBlau);
}