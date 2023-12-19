// C++ code
//
// #include <wire.h>
#include <LiquidCrystal_I2C.h>
// Set the LCD adresee to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(32, 16, 2);

void setup()
{
  lcd.init();

  lcd.backlight();
  
  lcd.print("Willkommen");
}

void loop()
{
  delay(1000);
  lcd.clear();
  lcd.print("Hello World");
  delay(1000); // Wait for 1000 millisecond(s)
  lcd.clear();
  delay(1000); // Wait for 1000 millisecond(s)
  lcd.print("Arduino");
  lcd.setCursor(0,1);
  lcd.print("ist interessant");
}