#include "button.h"

// Initialize static variables
bool Button::isButtonPress = false;
unsigned long Button::pressStartTime = 0;

Button::Button(int pin)
{
    _pin = pin;
    pinMode(_pin, INPUT); // Set button pin to INPUT_PULLUP mode
}

bool Button::isClick()
{
    unsigned int buttonState = digitalRead(_pin);
    unsigned long currentTime = millis();

    if (buttonState == LOW)
    { // Button is pressed
        if (!isButtonPress)
        { // If this is the first time the button is pressed
            isButtonPress = true;
            pressStartTime = currentTime; // Record the time the button was pressed
        }

        if (currentTime - pressStartTime > 50)
        {                // Button press duration threshold
            return true; // Valid click detected
        }
    }
    else
    {                          // Button is released
        isButtonPress = false; // Reset button press state when released
    }

    return false; // No click detected
}
