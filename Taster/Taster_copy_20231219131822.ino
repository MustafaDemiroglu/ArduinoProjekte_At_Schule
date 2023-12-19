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

void setup()
{
  pinMode(ledRot, OUTPUT);
  pinMode(ledGruen, OUTPUT);
  pinMode(ledBlau, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  wertRot = analogRead(reglerRot)/4;
  wertGruen = analogRead(reglerGruen)/4;
  wertBlau = analogRead(reglerBlau)/4;
  
  summeNeu = wertRot + wertGruen + wertBlau; 
  
  if(summe != summeNeu){
    /*
    Serial.print("Rot: ");
  	Serial.println(wertRot);
  
  	Serial.print("Gruen: ");
  	Serial.println(wertGruen);
  
  	Serial.print("Blau: ");
  	Serial.println(wertBlau);
    */
    
    farbe = "Farbe(RGB) : "+String(wertRot)+", "+String(wertGruen)+", "+String(wertBlau); 
    Serial.println(farbe);
    
    summe = summeNeu;
  }
  
  analogWrite(ledRot,wertRot);
  analogWrite(ledGruen,wertGruen);
  analogWrite(ledBlau,wertBlau);
}