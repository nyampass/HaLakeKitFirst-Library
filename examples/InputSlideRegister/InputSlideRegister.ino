#include "HaLakeKitFirst.h"
#define ANALOG_READ_PIN 7

HaLakeKitFirst kitFirst(&Serial);

void setup() {
  kitFirst.begin();
}

void loop() {
  kitFirst.sendValue(analogRead(ANALOG_READ_PIN),
                     500,
                     1000);
  delay(50);
}
