#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x26, 16, 2);

// function declaration
void buttonHandler();
void sensorHandler();

// button parameter
#define BTN_RESET_PIN D5
#define BTN_RESET_TOTAL_PIN D6

bool isResetPressed = false;
bool isResetTotalPressed = false;

unsigned long currentTime = 0;
unsigned long previousResetTime = 0;
unsigned long previousResetTotalTime = 0;
unsigned int debounceTime = 100;

/// sensor parameter
#define SENSOR_PIN D7
unsigned int count = 0;
unsigned int totalCount = 0;
unsigned int previousCount = 0;
bool sensorState = false;
unsigned long previousSensorTime = 0;

void setup()
{
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();

  pinMode(BTN_RESET_PIN, INPUT);
  pinMode(BTN_RESET_TOTAL_PIN, INPUT);
}

void loop()
{
  buttonHandler();
  sensorHandler();

  if (isResetPressed == true)
  {
    count = 0;
  }
  if (isResetTotalPressed == true)
  {
    count = 0;
    totalCount = 0;
  }

  if (count != previousCount)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Count: ");
    lcd.print(count);
    lcd.setCursor(0, 1);
    lcd.print("Total: ");
    lcd.print(totalCount);
    previousCount = count;
  }
}

void buttonHandler()
{
  currentTime = millis();
  if (digitalRead(BTN_RESET_PIN) == LOW && currentTime - previousResetTime > debounceTime)
  {
    isResetPressed = true;
    previousResetTime = currentTime;
  }
  else
  {
    isResetPressed = false;
  }

  if (digitalRead(BTN_RESET_TOTAL_PIN) == LOW && currentTime - previousResetTotalTime > debounceTime)
  {
    isResetTotalPressed = true;
    previousResetTotalTime = currentTime;
  }
  else
  {
    isResetTotalPressed = false;
  }
}

void sensorHandler()
{
  if (digitalRead(SENSOR_PIN) == LOW && sensorState == false)
  {
    sensorState = true;
  }
  else if (digitalRead(SENSOR_PIN) == HIGH && sensorState == true)
  {
    sensorState = false;
    count++;
    totalCount++;
  }
}