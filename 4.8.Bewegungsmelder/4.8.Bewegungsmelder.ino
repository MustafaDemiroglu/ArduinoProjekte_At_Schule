// C++ code
//

int sensor = 13;
int LED = 2;
int sensorStatus = 0;

void setup()
{
  pinMode(sensor, INPUT);
  pinMode(LED,OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  sensorStatus = digitalRead(sensor);
  Serial.println(sensorStatus);
  delay(1000);
  if(sensorStatus == 1){
    Serial.println("Katze ist da");
    Serial.println(millis());
    digitalWrite(LED, HIGH);
    delay(5000);
  } else {
    Serial.println("Katze schläft oder ist schon weg");
    digitalWrite(LED, LOW);
  }
}