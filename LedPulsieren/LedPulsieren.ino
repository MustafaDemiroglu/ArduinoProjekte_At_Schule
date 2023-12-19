// C++ code
// Variablen
int LEDrot = 13;
int LEDorange = 4;
int LEDgruen = 2;
int warteZeit = 1000; 
void setup()
{
  pinMode(LEDrot, OUTPUT);
  pinMode(LEDorange, OUTPUT);
  pinMode(LEDgruen, OUTPUT);
}

void loop()
{
  digitalWrite(LEDrot, HIGH);
  delay(warteZeit);
  digitalWrite(LEDrot, LOW);
  digitalWrite(LEDorange, HIGH);
  delay(warteZeit);
  digitalWrite(LEDorange, LOW);
  digitalWrite(LEDgruen, HIGH);
  delay(warteZeit);
  digitalWrite(LEDgruen, LOW);
}