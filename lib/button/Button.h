#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

class Button
{
public:
    // Constructor to initialize the button pin
    Button(int pin);

    // Method to check if the button is clicked
    bool isClick();

private:
    int _pin;                            // Pin connected to the button
    static bool isButtonPress;           // Track button press state across function calls
    static unsigned long pressStartTime; // Track the time when button press started
};

#endif
