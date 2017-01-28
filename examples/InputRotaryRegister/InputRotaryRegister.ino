#include "HaLakeKitFirst.h"
#include <Servo.h>

#define ANALOG_READ_POWER_PIN 7

HaLakeKitFirst kitFirst(&Serial);

void setup() {
  kitFirst.begin();
  pinMode(ANALOG_READ_POWER_PIN, INPUT);
}

void loop() {
  kitFirst.sendValue(analogRead(ANALOG_READ_POWER_PIN),
                     500,
                     1023);
  delay(20);
}
