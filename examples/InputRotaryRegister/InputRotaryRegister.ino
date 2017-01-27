#include "HaLakeKitFirst.h"
#include <Servo.h>

#define ANALOG_READ_POWER_PIN 7

HaLakeKitFirst kitConnector(&Serial);

int powerValue;
int outValue;

void setup() {
  kitConnector.begin();
  pinMode(ANALOG_READ_POWER_PIN, INPUT);
}

void loop() {
  powerValue = analogRead(ANALOG_READ_POWER_PIN);

  outValue = (powerValue - 500) * ((float) 1023 / 500);
  if (outValue < 0) {
    outValue = 0;
  } else if (outValue > 1023) {
    outValue = 1023;
  }

  kitConnector.sendValue(outValue);
  delay(20);
}
