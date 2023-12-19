// C++ code
//
#include <Adafruit_LiquidCrystal.h>
#include <Keypad.h>
#include <Servo.h>

Servo motor;  
int ledGruen = 10;
int ledRot = 11;
int pieps = 12;
 
const byte COLS = 4;
const byte ROWS = 4;
 
char hexaKeys[ROWS][COLS] ={
  {'D', '#', '0', '*'},
  {'C', '9', '8', '7'},
  {'B', '6', '5', '4'},
  {'A', '3', '2', '1'}
};
 
byte colPins[COLS] = {2, 3, 4, 5};
byte rowPins[ROWS] = {6, 7, 8, 9};
 
char Taste;
 
String geheim = "";	// Passwort
 
Keypad Tastenfeld = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
 
int cursorPos = 0;
 
Adafruit_LiquidCrystal lcd(0);
 
void setup(){
  motor.attach(13,500,2500);
  pinMode (ledGruen,OUTPUT);
  pinMode (ledRot,OUTPUT);
  pinMode (pieps,OUTPUT);
  lcd.begin(16, 2);
  lcd.print("Code?");
  Serial.begin(9600);
}

void offenTuer(){
    lcd.clear();
    lcd.print("Codewort erkannt");
    cursorPos = 0;
    lcd.setCursor(0, 1);
  	lcd.print("Tuer ist offen");
  	digitalWrite(ledRot,LOW);
  	for (int pos = 0; pos <= 180; pos += 1) {
    	// tell servo to go to position in variable 'pos'
    	motor.write(pos);
        digitalWrite(ledGruen,HIGH);
        digitalWrite(pieps,HIGH);
    	// wait 15 ms for servo to reach the position
    	delay(15); // Wait for 15 millisecond(s)
  	}
     
  	geheim ="";
}

void schliessTuer(){
  digitalWrite(ledGruen,LOW);
  digitalWrite(ledRot,HIGH);
  for (int pos = 180; pos >= 0; pos -= 1) {
    motor.write(pos);
    delay(15);
  }
  digitalWrite(pieps,LOW);
  lcd.clear();
  lcd.print("Tuer geschlossen");
}
 
void loop(){
  Taste = Tastenfeld.getKey();
  if(Taste){
    lcd.setCursor(cursorPos, 1);
    lcd.print(Taste); // Anzeige der eingegebenen Ziffern
    cursorPos = cursorPos + 1;
    Serial.print(" Taste: ");
    Serial.print(Taste);
    Serial.println();
    geheim += Taste;
    Serial.print(geheim);
    
    if(cursorPos == 4){
      if(geheim == "2303"){
        offenTuer();
        delay(3000);
        schliessTuer();
        geheim ="";
        lcd.clear();
        lcd.print("Code?");
        cursorPos = 0;
      } else {
        lcd.clear();
        lcd.print("Falscher Code!");
        delay(1000);
        geheim ="";
        lcd.clear();
        lcd.print("Code?");
        cursorPos = 0;
      }
    } else if(cursorPos > 4) { // Nur vier Ziffern erlaubt
      lcd.clear();
      lcd.print("Code zu lang");
      delay(1000);
      lcd.clear();
      geheim ="";
      lcd.print("Code?");
      cursorPos = 0;
    }
  }
}