// C++ code
// Variablen

int LED = 3;
int helligkeit = 0;
int x = 5;
int pause = 20;

void setup()
{
  pinMode(LED, OUTPUT);
}

void loop()
{
  analogWrite(LED, helligkeit);
  
  // Helligkeit verändern
  helligkeit += x;
  delay(pause);
  
  if(helligkeit == 255 || helligkeit == 255){
    // Vorzeichenwechsel
  	x = -x;
  }
  
}