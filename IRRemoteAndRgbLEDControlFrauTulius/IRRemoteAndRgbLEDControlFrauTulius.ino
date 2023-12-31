// das Projekt haben wir noch nie versucht. Frau Tulius hat uns nur gezeigt
// import Library
#include <IRremote.h>

// Define Pins
int redLed = 5;
int greenLed = 3;
int blueLed = 4;
int RECV_PIN = 11;

// IR Library stuff
IRrecv irrecv(RECV_PIN);
decode_results results;


void setup()
{
  //Set Led Pins
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(blueLed, OUTPUT);
  
  //Enable serial usage and IR signal in
  Serial.begin(9600);
  Serial.println("Enabling IRin");
  irrecv.enableIRIn(); 
  Serial.println("Enabled IRin");
}

void loop() {
  if (irrecv.decode(&results)) {
    //irrecv.decode(&results) returns true if anything is recieved, and stores info in varible results
    unsigned int value = results.value; 
    //Get the value of results as an unsigned int, so we can use switch case
    Serial.println(value);
    switch (value) {
      case 2295: 
      	digitalWrite(redLed, HIGH);
      	delay(500);
      	digitalWrite(redLed, LOW);
      	break;
      
      case 34935:
      	digitalWrite(blueLed, HIGH);
      	delay(500);
      	digitalWrite(blueLed, LOW);
      
      case 18615:
      	digitalWrite(greenLed, HIGH);
      	delay(500);
      	digitalWrite(greenLed, LOW);
      	break;
      
      
    }
    
    
    irrecv.resume(); // Receive the next value
  }
}
