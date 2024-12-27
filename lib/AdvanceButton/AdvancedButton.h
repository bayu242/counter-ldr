#ifndef ADVANCED_BUTTON_H
#define ADVANCED_BUTTON_H

#include <Arduino.h>

class AdvancedButton {
public:
    AdvancedButton(uint8_t pin);
    void begin();
    bool isSingleClick();
    bool isDoubleClick();
    bool isLongPress();

private:
    uint8_t _pin;
    bool _lastState;
    bool _currentState;
    unsigned long _lastDebounceTime;
    unsigned long _lastPressTime;
    unsigned long _pressDuration;
    const unsigned long _debounceDelay = 100; // milliseconds
    const unsigned long _doubleClickDelay = 500; // milliseconds
    const unsigned long _longPressDuration = 1000; // milliseconds
};

#endif // ADVANCED_BUTTON_H
