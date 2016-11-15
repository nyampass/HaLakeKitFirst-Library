#include "PushButton.h"

PushButton::PushButton(int _pin, int _pushedValue, unsigned long _switchBufferMillis) {
  pin = _pin;
  pushedValue = _pushedValue;
  switchBufferMillis = _switchBufferMillis;
  freeState = 0;
}

void PushButton::update() {
  pinValue = digitalRead(pin);
  if (pinValue == pushedValue) {
    if (pushedFromMillis == 0) {
      pushedFromMillis = millis();
    }
  } else {
    pushedFromMillis = 0;
  }
}

void PushButton::setup(int inputMode) {
  pinMode(pin, inputMode);
}

bool PushButton::isPushed(bool considerBufferMillis) {
  if (pinValue != pushedValue) {
    return false;
  }
  if (! considerBufferMillis) {
    return pushedFromMillis != 0;
  }
  return millis() - pushedFromMillis > switchBufferMillis;
}
