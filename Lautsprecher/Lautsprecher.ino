// C++ code
//
#include <Servo.h>

Servo servo;

#include <Keypad.h>

#include <Adafruit_LiquidCrystal.h>

Adafruit_LiquidCrystal lcd(0);

const byte COLS = 4;
const byte ROWS = 4;
char hexaKeys[ROWS][COLS]= {
  {'D', '#', '0', '*'},
  {'C', '9', '8', '7'},
  {'B', '6', '5', '4'},
  {'A', '3', '2', '1'}
};
byte colPins[COLS] = {2,3,4,5};
byte rowPins[ROWS] = {6,7,8,9};

char taste;

String zahlenFolge;

String passwort = "1234";

int ledRot = 10;
int ledGruen = 11;

Keypad tastenfeld = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void motorSteuerung()
  {
  	digitalWrite(ledGruen, HIGH);
    servo.write(0);
    delay(2000);
    servo.write(90);
  	digitalWrite(ledGruen, LOW);
  
  }

void setup()
{
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.setBacklight(1);
  servo.attach(13);
  pinMode(ledRot, OUTPUT);
  pinMode(ledGruen, OUTPUT);
}

void loop()
{
  taste = tastenfeld.getKey();
  if(taste)
  {
    Serial.print(taste);
    zahlenFolge = zahlenFolge + taste;
    lcd.clear();
  	lcd.setCursor(0,0);
  	lcd.print(zahlenFolge);
    if(zahlenFolge == passwort)
    {
      lcd.clear();
      lcd.print("Success");
      zahlenFolge = "";
      motorSteuerung();
    }
    else if (zahlenFolge.length() >=4)
    {
      lcd.clear();
      lcd.print("Wrong PW");
      zahlenFolge = "";
      digitalWrite(ledRot, HIGH);
      delay(2000);
      digitalWrite(ledRot, LOW);
    }
  }
}