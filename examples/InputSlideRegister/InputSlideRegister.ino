#include "HaLakeKitFirst.h"
#define ANALOG_READ_PIN 7

int receivedValue;
int outValue;

HaLakeKitFirst kitConnector(&Serial);

void setup() {
  kitConnector.begin();
}

void loop() {
  receivedValue = analogRead(ANALOG_READ_PIN);

  outValue = (receivedValue - 500) * ((float) 1023 / 500);
  if (outValue < 0) {
    outValue = 0;
  } else if (outValue > 1023) {
    outValue = 1023;
  }

  kitConnector.sendValue(outValue);

  delay(50);
}
