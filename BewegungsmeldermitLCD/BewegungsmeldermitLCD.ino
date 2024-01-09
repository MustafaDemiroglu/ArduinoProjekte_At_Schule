// C++ code
// Bibliotheken importieren
#include <Adafruit_LiquidCrystal.h>
#include <Keypad.h>

// ###### Tastenfeld ######
const byte COLS = 4;
const byte ROWS = 4 ;

// Tastenbelegung
char hexaKeys[ROWS][COLS] = {
  {'D','#','0','*'},
  {'C','9','8','7'},
  {'B','6','5','4'},
  {'A','3','2','1'}  
};

// Pinbelegung
byte colPins[COLS] = {5,6,7,8};
byte rowPins[ROWS] = {9,10,11,12};

// Objekt erzeugen
Keypad Tastenfeld = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

// wird später benötigt zur abfrage der gedrückten Taste
char Taste;

// ######## LCD-Display #######
Adafruit_LiquidCrystal display(0);
int cursorPos = 0;
String openAnzeige = "Tuer ist sicher";
String bewegungAnzeige = "Bewegung !!!";
String closeAnzeige = "Code?";
String fehlerAnzeige = "4-stelliger code";
String falscherCodeAnzeige = "falsch Code!";

// ##### PIEZO ######
int piezo = 3;

// ###### LED ########
int LED = 2;

// ###### SENSOR ########
int sensor = 13;
int sensorStatus = 0;

// ###### SAFE ######
String passwort ="1234";
String kontrolPasswort ;
String eingabe;
boolean open = true;

// ##### einige Methoden #####
void wechselAnzeige(String anzeige) {
  display.clear();
  display.print(anzeige);
  cursorPos = 0;
}

void setup()
{
  // Safe ist sicher
  display.begin(16,2);
  display.print(openAnzeige);
  
  // Sensor
  pinMode(sensor, INPUT);
  
  //LED
  pinMode(LED,OUTPUT);
  
  // Piezo - Lautsprecher
  pinMode(piezo, OUTPUT);
  
  Serial.begin(9600);
}

void loop()
{
  sensorStatus = digitalRead(sensor);
  Serial.println(sensorStatus);
  delay(500);
  
  if(sensorStatus == 1){
    Serial.println("Bewegung !!!");
    Serial.println(millis());
    digitalWrite(LED, HIGH);
    digitalWrite (piezo, HIGH);
    wechselAnzeige(bewegungAnzeige);
    delay(500); 
    wechselAnzeige(closeAnzeige);
    delay(500);
    display.clear();
    while (kontrolPasswort != passwort) {
      // warten auf Tasteneingabe
      Taste = Tastenfeld.getKey();
      // Bewegung! und wartet auf Eingabe fuer Passwort zu kontrollieren 
      // Zulässig 0-9 und a-D
      if(Taste !='*' and Taste !='#') {
        if(Taste and eingabe.length() <= 4){
          // display Zeile eintellen
          display.setCursor(cursorPos, 1);
          // gedrückte auf Dispaly anzeigen
          display.print(Taste);
          // gedrückte auf Display schieben  
          cursorPos = cursorPos + 1;
          // eingabe merken und in eingabe speichern
          eingabe = eingabe + Taste;
        }
      } //PassEingabe gespeichert
      // kontrolPasswort  bestätigen mit * --> Safe wird verriegelt
      if(Taste=='*'){
        if(eingabe.length() == 4){
          kontrolPasswort = eingabe;
          eingabe = "";

        } else {
          // Passwort war kürzer als 4 zeichen
          delay(500);
          wechselAnzeige(fehlerAnzeige);
          display.setCursor(cursorPos, 1);
          kontrolPasswort = "";
          eingabe = "";
          wechselAnzeige(openAnzeige);
        }
      } // Ende safe verriegeln

      // aktuelle Eingabe mit Passwort vergleichen
      if (passwort == kontrolPasswort){
        Serial.println("Keine Bewegung");
        digitalWrite(LED, LOW);
        digitalWrite (piezo, LOW);
        wechselAnzeige(openAnzeige);
        kontrolPasswort = "";
        eingabe = "";
        open = true;
      } // Safe offen  --> Startposition
      } 
    } else {
        display.print(openAnzeige);
      }
}