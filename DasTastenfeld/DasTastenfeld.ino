// C++ code
//
#include <Keypad.h>
#include <Adafruit_LiquidCrystal.h>

// Display
Adafruit_LiquidCrystal display(0);

// Tastenfeld
const byte COLS = 4;
const byte ROWS = 4;
byte colPins[4] = {5, 4, 3, 2};
byte rowPins [4] = {9, 8, 7, 6};
char hexaKeys[ROWS][COLS]={
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

char Taste;
Keypad Tastenfeld = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void setup()
{
  Serial.begin(9600);
  display.begin(16, 2);
  display.clear();
  display.print("Keine Auswahl");
}

void loop()
{
  Taste = Tastenfeld.getKey();
  if(Taste){
  	Serial.print(Taste);
    Serial.print(" wurde gedrueckt");
    Serial.println();
    display.clear();
    display.setCursor(0, 0);
    display.print(Taste);
    
  }
  if(Taste == 'A'){
  	Serial.print("Treffer");
    Serial.println();
    display.setCursor(0, 1);
    display.print("Treffer");
  }
}