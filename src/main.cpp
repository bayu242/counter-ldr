#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

// function
bool isClick(int pin);

#define btnTotalReset D7
#define btnReset D6
#define sensorPin D5

// variabel

unsigned int count = 0;
unsigned int totalCount = 0;

LiquidCrystal_I2C lcd(0x26, 16, 2);

void setup()
{
  Serial.begin(115200);
  pinMode(btnReset, INPUT_PULLUP);
  pinMode(sensorPin, INPUT_PULLUP);
  pinMode(btnTotalReset, INPUT_PULLUP);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Counter Machine");
  delay(2000);
}

void loop()
{
  if (isClick(btnReset) == true)
  {
    count++;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Count: ");
    lcd.print(count);
    Serial.println(count);
  }

  if (isClick(btnTotalReset) == true)
  {
    count = 0;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Count: ");
    lcd.print(count);
    Serial.println(count);
  }
}

bool isClick(int pin)
{
  int buttonState = digitalRead(pin);
  bool isButtonPress = false;
  unsigned long pressStartTime = 0;

  if (buttonState == LOW)
  {
    if (!isButtonPress)
    {
      isButtonPress = true;
      pressStartTime = millis();
    }

    if (millis() - pressStartTime > 50)
    {
      isButtonPress = false;
      return true;
    }
  }
  else
  {
    isButtonPress = false;
  }
  return false;
}