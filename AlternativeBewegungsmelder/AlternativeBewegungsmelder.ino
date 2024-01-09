int sensor = 13;
int LED = 2;
int sensorStatus = 0;
int lastMovement = 0;

void setup()
{
  pinMode(sensor, INPUT);
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}


void loop()
{
  sensorStatus = digitalRead(sensor);
  int curts = millis();
  
  if(sensorStatus == 1) {
    lastMovement = curts;
  }
  
  if(lastMovement && curts - lastMovement < 30) {
    Serial.println("Bewegung in den letzten 3 Sekunden");
    digitalWrite(LED, HIGH);
  } else {
    digitalWrite(LED, LOW);
  }
}