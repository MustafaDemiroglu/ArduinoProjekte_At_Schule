// C++ code
// Variablen deklarieren

const int MAX_LEVEL  = 100;
int sequence[MAX_LEVEL];
int your_sequence[MAX_LEVEL];
int level = 0;
int punkte = 0;
int velocity = 1000;
int highscore = 1;

// ##### PIEZO ######
int piezo = 6;

// ##### LCD #####
#include <Adafruit_LiquidCrystal.h>
Adafruit_LiquidCrystal display(0);
String openAnzeige = " Willkommen !!! ";
String startAnzeige = "Druecken Start";
String richtigAnzeige = "Bestanden";
String falschAnzeige = "leider Falsch";
String glueckAnzeige = "Viel Glueck !!!";

void setup() 
{  
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);

  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);

  // Piezo - Lautsprecher
  pinMode(piezo, OUTPUT);  

  // Lcd initialisieren
  display.begin(16,2);
  delay(250);
  
  Serial.begin(9600);
  /*
  	Serial.print(" Stuffe 0 : Level = ");
    Serial.println(level);
    Serial.print(" Stuffe 0 : Pnukte = ");
    Serial.println(punkte);
   */ 
}

void loop()
{
    /*
    digitalWrite(2, HIGH);
    Serial.print(" Stuffe 1 : Level = ");
    Serial.println(level);
    Serial.print(" Stuffe 1 : Pnukte = ");
    Serial.println(punkte);
    */
  if (level == 0){
  	display.print(openAnzeige);
    digitalWrite (piezo, HIGH);
    delay(250);
    display.clear();
    display.print(startAnzeige);
    delay(250);
    display.clear();
    digitalWrite (piezo, LOW);
    level++;
      Serial.print(" Stuffe 2 : Level = ");
      Serial.println(level);
      Serial.print(" Stuffe 2 : Pnukte = ");
      Serial.println(punkte);
    generate_sequence();
  } 
  
   // If start button is pressed or you're winning
   if (digitalRead(A4) == LOW || level != 1){  
          Serial.print(" Stuffe 4 : Level = ");
          Serial.println(level);
          Serial.print(" Stuffe 4 : Pnukte = ");
          Serial.println(punkte);
     	showPunkte();
        show_sequence();    
        get_sequence(); 
   }
  		Serial.print(" Stuffe 10 : Level = ");
        Serial.println(level);
  		Serial.print(" Stuffe 10 : Pnukte = ");
  		Serial.println(punkte);
}

void  show_sequence()
{
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);

  for (int i = 0; i < level; i++){
    digitalWrite(sequence[i],  HIGH);
    delay(velocity);
    digitalWrite(sequence[i], LOW);
    delay(200);
  }
  
  		Serial.print(" Stuffe 5 : Level = ");
        Serial.println(level);
  		Serial.print(" Stuffe 5 : Pnukte = ");
  		Serial.println(punkte);
}

void  get_sequence()
{  
        Serial.print(" Stuffe Test get_sequence(): Level = ");
        Serial.println(level);
  		Serial.print(" Stuffe Test get_sequence(): Pnukte = ");
  		Serial.println(punkte);
  
  int flag = 0; //this flag indicates if the sequence is correct

  for  (int i = 0; i < level; i++)
  {
    flag = 0;
    while(flag == 0)
    {
      if (digitalRead(A0)  == LOW)
      {
        digitalWrite(5, HIGH);
        tone(piezo,300);  
        your_sequence[i] = 5;
        flag = 1;
        delay(200);
        noTone(piezo);
        if  (your_sequence[i] != sequence[i])
        {
          wrong_sequence();
              Serial.print(" Stuffe 6,1 : Level = ");
              Serial.println(level);
              Serial.print(" Stuffe 6,1 : Pnukte = ");
              Serial.println(punkte);
          return;
        }
        digitalWrite(5,  LOW);
      }

      if (digitalRead(A1) == LOW)
      {
        digitalWrite(4, HIGH);
        tone(piezo, 280);
        your_sequence[i] = 4;
        flag = 1;
        delay(200);
        noTone(piezo);
        if (your_sequence[i] != sequence[i])
        {
          wrong_sequence();
              Serial.print(" Stuffe 6,2 : Level = ");
              Serial.println(level);
              Serial.print(" Stuffe 6,2 : Pnukte = ");
              Serial.println(punkte);
          return;
        }
        digitalWrite(4,  LOW);
      }

      if (digitalRead(A2) == LOW)
      {
        digitalWrite(3, HIGH);
        tone(piezo, 260);
        your_sequence[i] = 3;
        flag = 1;
        delay(200);
        noTone(piezo);
        if (your_sequence[i] != sequence[i])
        {
          wrong_sequence();
              Serial.print(" Stuffe 6,3 : Level = ");
              Serial.println(level);
              Serial.print(" Stuffe 6,3 : Pnukte = ");
              Serial.println(punkte);
          return;
        }
        digitalWrite(3,  LOW);
      }

      if (digitalRead(A3) == LOW)
      {
        digitalWrite(2, HIGH);
        tone(piezo, 240);
          your_sequence[i] = 2;
          flag = 1;
          delay(200);
          noTone(piezo);
        if (your_sequence[i] != sequence[i])
        {
          wrong_sequence();
              Serial.print(" Stuffe 6,4 : Level = ");
              Serial.println(level);
              Serial.print(" Stuffe 6,4 : Pnukte = ");
              Serial.println(punkte);
          return;
        }
        digitalWrite(2,  LOW);
      }
    }
  }
  	    Serial.print(" Stuffe 7,1 : Level = ");
        Serial.println(level);
  		Serial.print(" Stuffe 7,1 : Pnukte = ");
  		Serial.println(punkte);
  right_sequence();
  		Serial.print(" Stuffe 7,2 : Level = ");
        Serial.println(level);
  		Serial.print(" Stuffe 7,2 : Pnukte = ");
  		Serial.println(punkte);
}

void generate_sequence()
{
  randomSeed(millis());  //in this way is really random!!!
    Serial.print(" Stuffe 3,1 : Level = ");
    Serial.println(level);
    Serial.print(" Stuffe 3,1 : Pnukte = ");
    Serial.println(punkte);

  for (int i = 0; i < MAX_LEVEL; i++)
  {
  	sequence[i]  = random(2,6);
  }
    Serial.print(" Stuffe 3,2 : Level = ");
    Serial.println(level);
    Serial.print(" Stuffe 3,2 : Pnukte = ");
    Serial.println(punkte); 
}

void wrong_sequence()
{
 	    Serial.print(" Stuffe 8,1 : Level = ");
        Serial.println(level);
  		Serial.print(" Stuffe 8,2 : Pnukte = ");
  		Serial.println(punkte);
  for (int i = 0; i < 3;  i++)
  {
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4,  HIGH);
    digitalWrite(5, HIGH);
    tone(piezo, 1000);
    delay(250); 
    noTone(piezo); 
    digitalWrite(2, LOW);
    digitalWrite(3,  LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    delay(250);
  }
  level  = 0;
  velocity = 1000;
  wechselAnzeige(falschAnzeige);
        Serial.print(" Stuffe 8,2 : Level = ");
        Serial.println(level);
  		Serial.print(" Stuffe 8,2 : Pnukte = ");
  		Serial.println(punkte);
}

void right_sequence()
{
  		Serial.print(" Stuffe 9,1 : Level = ");
        Serial.println(level);
  		Serial.print(" Stuffe 9,1 : Pnukte = ");
  		Serial.println(punkte);
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  delay(200); 
  
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite (piezo, HIGH);
  delay(300);  
  
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite (piezo, LOW);
  delay(100);
  
  wechselAnzeige(richtigAnzeige);
  
  punkte++;
  if(highscore < level){
      highscore = punkte;
    }
  
  if  (level < MAX_LEVEL){
    level++;
    velocity -= 50; //increase difficulty
  } else {
  	level = MAX_LEVEL;
  }
  		Serial.print(" Stuffe 9,2 : Level = ");
        Serial.println(level);
  		Serial.print(" Stuffe 9,2 : Pnukte = ");
  		Serial.println(punkte);
  
}

// ##### einige Methoden #####
void wechselAnzeige(String anzeige) {
  display.clear();
  display.print(anzeige);
  delay(300);
  display.clear();
}

void showPunkte(){
  display.clear();
  display.setCursor(0,0);
  display.print("Level: ");
  display.print(level);
  display.setCursor(0,1);
  display.print("Highscore: ");
  display.print(highscore);
  delay(1000);
  display.clear();
}