#include "HaLakeKitFirst.h"
#define LED_PIN 10

HaLakeKitFirst kitFirst(&Serial);

int outValue;

void setup() {
  kitFirst.begin();
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  if (kitFirst.receive()) {
    outValue = kitFirst.getReceivedValue(0, 255);
  } else {
    outValue = 0;
  }

  analogWrite(LED_PIN, outValue);
}
