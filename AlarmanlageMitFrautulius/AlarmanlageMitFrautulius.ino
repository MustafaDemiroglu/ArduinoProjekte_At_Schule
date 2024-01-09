// C++ code

// Bibliotheken
#include <Adafruit_LiquidCrystal.h>
#include <Keypad.h>

// Variablen
int sensor = 13;
int sensorStatus = 0;
int LED = 12;
int ton = 11;

// Display
Adafruit_LiquidCrystal display(0);
int cursorPos = 0;
String ruheAnzeige = "Alles ruhig!";
String alarmAnzeige = "Bewegung!!";


// Tastenfeld
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

Keypad Tastenfeld = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

// Hilfsvariablen
boolean code = false;
boolean alarm = false;
String eingabe = "";
String passwort = "2303";

// Eigene Funktionen
void alarmAusschalten(){
	digitalWrite(LED, LOW);
  	digitalWrite(ton, LOW);
  	display.clear();
  	display.print(ruheAnzeige);
  	alarm = false;
 	eingabe = "";
  	//Serial.print("Alarm aus");  
}

void alarmEinschalten(){
    digitalWrite(LED, HIGH);
    //digitalWrite(ton, HIGH);
    display.clear();
    display.print(alarmAnzeige);
    alarm = true;
  	//Serial.print("Alarm ausgelöst");

}

void pwEingabe(){
  Taste = Tastenfeld.getKey();
  
  if (Taste == '#'){
    display.clear();
    display.print(alarmAnzeige);
    eingabe = "";
    cursorPos = 0;
  }
  
  if (Taste != NO_KEY && Taste != '#' && Taste != '*' && eingabe.length() < 4) {
    display.setCursor(cursorPos, 1);
    display.print(Taste);
    cursorPos = cursorPos + 1;
    eingabe = eingabe + Taste;
  }
  

    if (eingabe == passwort && Taste == '*') {
      alarmAusschalten();
      cursorPos = 0;
      eingabe = "";
      delay(3000);
    }
  }



void setup()
{
	pinMode(sensor, INPUT);
  	pinMode(LED, OUTPUT);
  	pinMode(ton, OUTPUT);
 	display.begin(16,2);
	display.print(ruheAnzeige);  
  
  	// zum Testen auf Konsole
  	//Serial.begin(9600);
}

void loop()
{
  sensorStatus = digitalRead(sensor);
  //Serial.println(sensorStatus);
  
  
  if(sensorStatus == 1 && !alarm){
	alarmEinschalten();
  }
  
  if(alarm){
   pwEingabe();
  
  }
  
   

	
}












