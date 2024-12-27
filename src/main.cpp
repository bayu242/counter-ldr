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

  lcd.setCursor(0, 0);
  lcd.print("Counter Machine");
  delay(2000);
  lcd.clear();
}

void loop()
{
  //add funcrtion to loop
  buttonHandler();
  sensorHandler();

  char countBuffer[16];
  sprintf(countBuffer, "Count: %d", count);
  char totalCountBuffer[16];
  sprintf(totalCountBuffer, "Total: %d", totalCount);
  lcd.setCursor(0, 0);
  lcd.print(countBuffer);
  lcd.setCursor(0, 1);
  lcd.print(totalCountBuffer);
}

//button handler
void buttonHandler()
{
  currentTime = millis();

  //reset count
  if (digitalRead(BTN_RESET_PIN) == LOW && currentTime - previousResetTime > debounceTime)
  {
    count = 0;
    previousResetTime = currentTime;
    lcd.clear();
  }

  //reset count and total count
  if (digitalRead(BTN_RESET_TOTAL_PIN) == LOW && currentTime - previousResetTotalTime > debounceTime)
  {
    count = 0;
    totalCount = 0;
    previousResetTotalTime = currentTime;
    lcd.clear();
  }
}

//sensor handler
void sensorHandler()
{
  //read sensor and triger count
  if (digitalRead(SENSOR_PIN) == LOW && sensorState == false)
  {
    sensorState = true;
  }
  else if (digitalRead(SENSOR_PIN) == HIGH && sensorState == true)
  {
    sensorState = false;
    count++;
    totalCount++;
    lcd.clear();
  }
}