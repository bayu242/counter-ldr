#include <Arduino.h>
#include <Wire.h>
#include "AdvancedButton.h"
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x26, 16, 2); // Set the LCD I2C address and dimensions

AdvancedButton button(D6); // Attach button to pin D6

void setup()
{
  Serial.begin(115200);
  button.begin();
  lcd.init();      // Initialize the LCD
  lcd.backlight(); // Turn on the backlight
}

void loop()
{
  if (button.isSingleClick())
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Single click");
  }

  if (button.isDoubleClick())
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Double click");
  }

  if (button.isLongPress())
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Long press");
  }
}
