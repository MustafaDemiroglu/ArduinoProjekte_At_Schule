// C++ code
//
#include <Keypad.h>
const byte COLS = 4;
const byte ROWS = 4;
char hexaKeys[ROWS][COLS]= {
  {'D','#','0','*'},
  {'C','9','8','7'},
  {'B','6','5','4'},
  {'A','3','2','1'}
};
byte colPins[COLS] = {2,3,4,5};
byte rowPins[ROWS] = {6,7,8,9}; 
char Taste;
Keypad Tastenfeld = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  Taste = Tastenfeld.getKey();
  if(Taste){
  	Serial.print(Taste);
    Serial.print(" wurde gedrueckt");
    Serial.println();
  }
}