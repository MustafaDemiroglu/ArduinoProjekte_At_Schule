// C++ code

// Bibliotheken importieren
# include <Adafruit_LiquidCrystal.h>
# include <Servo.h>
# include <Keypad.h>

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
byte colPins[COLS] = {2,3,4,5};
byte rowPins[ROWS] = {6,7,8,9};

// Objekt erzeugen
Keypad Tastenfeld = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

// wird später benötigt zur abfrage der gedrückten Taste
char Taste;

// ######## LCD-Display #######
Adafruit_LiquidCrystal display(0);
int cursorPos = 0;
String openAnzeige = "Wilkommen";
String closeAnzeige = "Code?";
String fehlerAnzeige = "4-stelliger code";
String falscherCodeAnzeige = "falsch Code!";

// ##### Servo-Motor ######
Servo servo;
int servoOpen = 0;
int servoClose = 90;

// ##### PIEZO ######
int piezo = 13;

// ###### LED ########
int rotLED = 12;
int gruenLED = 11;

// ###### SAFE ######
String passwort;
String eingabe;
boolean open = true;

// ##### einige Methoden #####
void wechselAnzeige(String anzeige) {
  display.clear();
  display.print(anzeige);
  cursorPos = 0;
}

// motorLaerm
void knatter() {
  digitalWrite(piezo, HIGH);
  delay(2000);
  digitalWrite(piezo, LOW);
}


void setup()
{
  // Safe ist geöffnet und wartet auf Passwort zum Verriegeln
  display.begin(16,2);
  display.print(openAnzeige);
  
  // Motor in Position open
  servo.attach(10);
  servo.write(servoOpen);
  
  // Piezo - Lautsprecher
  pinMode(piezo, OUTPUT);
  
  // LED (grün leuchtet, da Safe offen ist)
  pinMode(rotLED, OUTPUT);
  pinMode(gruenLED, OUTPUT);
  digitalWrite(gruenLED, HIGH);
}

void loop()
{
  // warten auf Tasteneingabe
  Taste = Tastenfeld.getKey();
  
  // Safe ist offen und wartet auf Eingabe Passwort zum Verrigeln
  // Zulässig 0-9 und a-D
  if(open and Taste !='*' and Taste !='#') {
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
  } //Passwort ist in Eingabe gespeichert
  
  // Passwort  betätigen mit * --> Safe wird verriegelt
  if(Taste=='*'){
    if(eingabe.length() == 4){
      passwort = eingabe;
      eingabe = "";
      
      // Motor Verriegelt Tür
      servo.write(servoClose);
      // Motorgräuscht
      knatter();
      
      // Anzeige wechseln --> von willkommen auf Code?
      wechselAnzeige(closeAnzeige);
      
      // LED grün geht aus, rot geht an
      digitalWrite(gruenLED, LOW);
      digitalWrite(rotLED, HIGH);
      
      open = false;
    } else {
      // Passwort war kürzer als 4 zeichen
      delay(500);
      wechselAnzeige(fehlerAnzeige);
      display.setCursor(cursorPos, 1);
      passwort = "";
      eingabe = "";
      wechselAnzeige(openAnzeige);
      
      
    }
  } // Ende safe verriegeln
  
  // Zustand Safe verriegelt
  if (!open and Taste !='*' and Taste !='#'){
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
  }
  
  // aktuelle Eingabe mit Passwort vergleichen
  if (passwort == eingabe and !open){
    // Motor entriegeln
    servo.write(servoOpen);
    // Motorgeräusch
    knatter();
    delay(500);
    wechselAnzeige(openAnzeige);
    // LED rot aus; grün an
    digitalWrite(rotLED, LOW);
    digitalWrite(gruenLED, HIGH);
    
    passwort = "";
    eingabe = "";
    open = true;
  } // Safe offen  --> Startposition
  
  // bei falschem Code
  if(!open and passwort.length() == 4 and eingabe.length() == 4 and passwort != eingabe){
    wechselAnzeige(falscherCodeAnzeige);
    eingabe = "";
    delay(500);
    wechselAnzeige(closeAnzeige);
  }
  
  // Eingabe zurücksetzen --> vertippt #
  if(Taste =='#'){
    eingabe = "";
    display.clear();
    if(open){
      display.print(openAnzeige);
    } else {
      display.print(closeAnzeige);
    }
    cursorPos = 0;
  }
  
  // TO Do ----> Aufgabe: Masterpasswort, max. Fehlersuche --> Rezeption kontaktieren
  
  
} // Ende Loop
  