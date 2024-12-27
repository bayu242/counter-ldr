#include "AdvancedButton.h"

AdvancedButton::AdvancedButton(uint8_t pin) : _pin(pin), _lastState(HIGH), _currentState(HIGH), _lastDebounceTime(0), _lastPressTime(0), _pressDuration(0) {}

void AdvancedButton::begin() {
    pinMode(_pin, INPUT_PULLUP);
}

bool AdvancedButton::isSingleClick() {
    int reading = digitalRead(_pin);
    if (reading != _lastState) {
        _lastDebounceTime = millis();
    }
    if ((millis() - _lastDebounceTime) > _debounceDelay) {
        if (reading != _currentState) {
            _currentState = reading;
            if (_currentState == LOW) {
                if ((millis() - _lastPressTime) > _doubleClickDelay) {
                    _lastPressTime = millis();
                    return true;
                }
            }
        }
    }
    _lastState = reading;
    return false;
}

bool AdvancedButton::isDoubleClick() {
    int reading = digitalRead(_pin);
    if (reading != _lastState) {
        _lastDebounceTime = millis();
    }
    if ((millis() - _lastDebounceTime) > _debounceDelay) {
        if (reading != _currentState) {
            _currentState = reading;
            if (_currentState == LOW) {
                if ((millis() - _lastPressTime) <= _doubleClickDelay) {
                    _lastPressTime = 0;
                    return true;
                }
                _lastPressTime = millis();
            }
        }
    }
    _lastState = reading;
    return false;
}

bool AdvancedButton::isLongPress() {
    int reading = digitalRead(_pin);
    if (reading != _lastState) {
        _lastDebounceTime = millis();
    }
    if ((millis() - _lastDebounceTime) > _debounceDelay) {
        if (reading != _currentState) {
            _currentState = reading;
            if (_currentState == LOW) {
                _pressDuration = millis();
            } else {
                if ((millis() - _pressDuration) >= _longPressDuration) {
                    return true;
                }
            }
        }
    }
    _lastState = reading;
    return false;
}
