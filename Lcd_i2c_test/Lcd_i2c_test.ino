#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup()
{
  lcd.begin(20,4); 
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("  I2C LCD with ");
  lcd.setCursor(0,1);
  lcd.print("  ESP32 DevKit ");
  //delay(2000);
}


void loop()
{
  
}
