#ifndef PushButton_h
#define PushButton_h

#include "Arduino.h"

class PushButton {
  public:
  int pin;
  bool pushedValue;
  unsigned long pushedFromMillis;
  unsigned long switchBufferMillis;
  bool pinValue;
  int freeState;

  PushButton(int _pin, int _pushedValue = HIGH, unsigned long _switchBufferMillis = 20);
  void update();
  void setup(int inputMode = INPUT);
  bool isPushed(bool considerBufferMillis = true);
};
#endif
