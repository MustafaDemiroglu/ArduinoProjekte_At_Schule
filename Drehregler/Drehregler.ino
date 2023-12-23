// C++ code
// fest code
void setup()
{
  pinMode(10, OUTPUT);
}

// schleife
void loop()
{
  digitalWrite(10, HIGH);
  delay(1000); // Wait for 1000 millisecond(s)
  digitalWrite(10, LOW);
  delay(1000); // Wait for 1000 millisecond(s)
}
