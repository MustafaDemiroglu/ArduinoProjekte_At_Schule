// C++ code
//

# include <Servo.h>
Servo motor;  

void setup()
{
  motor.attach(8);
}

void loop()
{
  motor.write(30);
  delay(1000);
  motor.write(45);
  delay(1000);
  motor.write(60);
  delay(1000);
  motor.write(75);
  delay(1000);
  motor.write(90);
  delay(1000);
  motor.write(75);
  delay(1000);
  motor.write(60);
  delay(1000);
  motor.write(45);
  delay(1000);
  motor.write(30);
  delay(1000);
  motor.write(15);
  delay(1000);
  motor.write(0);
  delay(1000);
  motor.write(15);
  delay(1000);  
}