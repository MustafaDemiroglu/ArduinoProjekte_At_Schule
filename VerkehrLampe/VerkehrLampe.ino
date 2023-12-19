// C++ code
//

int led = 8;
int taster = 2;
int status = 0;

void setup()
{
  pinMode(led, OUTPUT);
  pinMode(taster, INPUT);
}

void loop()
{
  status = digitalRead(taster);
  if (status == HIGH) {
  	digitalWrite(led, HIGH);
    delay(1000);
    digitalWrite(led,LOW);
  } else{
    	digitalWrite(led, LOW);
  }
}