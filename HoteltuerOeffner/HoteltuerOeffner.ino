// C++ code
//variablen
int eingang = A0; // das Wort "eingang" steht jetzt für den Wert "A0" (Bezeichnung vom Analogport 0) 
int LED = 13; // das wort "LED" steht jetzt für den Wert 13 
int sensorwert=0; // Variable für den Sensorwert mit 0 als Startwert 

void setup() // Hier beginnt das Setup
{
  pinMode(LED, OUTPUT); // Der Pin mit der LED(Pin 13) ist jetzt ein Ausgang
}

void loop() // Mit dieser klamme wird der Loop-Teil geöffnet
{
  sensorwert = analogRead(eingang); // Die Spannung am Drehregler wird auslesen und wie im vorherigen Sketch als Zahl zwischen 0 und 1023 unter der Variable "sensorwert" gespeichert 
  digitalWrite(LED, HIGH);
  delay(sensorwert); // Wait for sensorwert millisecond(s)
  digitalWrite(LED, LOW);
  delay(sensorwert); // Wait for sensorwert millisecond(s)
}