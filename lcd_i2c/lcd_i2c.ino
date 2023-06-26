#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  lcd.init();
  lcd.backlight();
}

void loop() {
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("Get Started");
  lcd.setCursor(0, 1);
  lcd.print("With Arduino");


  delay(2000);
}