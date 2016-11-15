#include "HaLakeKitFirstConnector.h"
#define LED_PIN 10

HaLakeKitFirstConnector kitConnector(&Serial);

String kitStr;
int receivedValue;
int outValue;

void setup() {
  kitConnector.begin();
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  kitStr = kitConnector.waitLine();
  receivedValue = kitConnector.valueFromLine(kitStr);

  if (receivedValue < 0) {
    outValue = 0;
  } else {
    outValue = receivedValue / 4;
  }

  analogWrite(LED_PIN, outValue);
}
