// C++ code
// Variablen
int ledRot1 = 8;
int ledGelb1 = 7;
int ledGruen1 = 6;
int ledRot2 = 3;
int ledGruen2 = 2;
int taster = 4;
int lautsprecher = 10;

int status = 0;
int pause = 2000;
void setup()
{
  pinMode(ledRot1, OUTPUT);
  pinMode(ledGelb1, OUTPUT);
  pinMode(ledGruen1, OUTPUT);
  pinMode(ledRot2, OUTPUT);
  pinMode(ledGruen2, OUTPUT);
  pinMode(lautsprecher, OUTPUT);
  pinMode(taster, INPUT);
}

void gruenRot(){
  delay(2000);
  digitalWrite(ledGruen1, LOW);
  digitalWrite(lautsprecher, LOW);
  digitalWrite(ledGelb1,HIGH);
  delay(2000);
  digitalWrite(ledGelb1, LOW);
  digitalWrite(ledRot1, HIGH);
  delay(1000);
}

void fussgaenger(){
  digitalWrite(ledRot2,LOW);
  digitalWrite(ledGruen2,HIGH);
  digitalWrite(lautsprecher,HIGH);
  // fussgaenger laufen
  delay(10000);
  digitalWrite(ledGruen2, LOW);
  digitalWrite(lautsprecher, LOW);
  digitalWrite(ledRot2, HIGH);
  delay(1000);
}

void rotGruen(){
  digitalWrite(ledRot1,LOW);
  digitalWrite(ledGelb1,HIGH);
  delay(2000);
  digitalWrite(ledRot1,LOW);
  digitalWrite(ledGelb1,LOW);
  digitalWrite(ledGruen1,HIGH);
  digitalWrite(lautsprecher,HIGH);
}

void loop()
{
  
  // Beginn Autos haben grün, Fussgänger rot
  digitalWrite(ledGruen1, HIGH);
  digitalWrite(lautsprecher,HIGH);
  digitalWrite(ledRot2, HIGH);
  
  // fussgänger kommt und drückt taster
  status = digitalRead(taster);
  
  if(status == HIGH) {
    // AUtos von gruen auf rot
    gruenRot();
    // fußgänger von rot auf grün
    fussgaenger();
    // Autos von rot auf grün
    rotGruen();
  }
}