#include "HaLakeKitFirst.h"
#include "PushButton.h"

#define UP_BUTTON_PIN 2
#define DOWN_BUTTON_PIN A0
#define MAX_VALUE 1023

HaLakeKitFirst kitConnector(&Serial);

int targetValue = 0;
PushButton upButton(UP_BUTTON_PIN, LOW);
PushButton downButton(DOWN_BUTTON_PIN, LOW);

void setup() {
  kitConnector.begin();

  upButton.setup(INPUT_PULLUP);
  downButton.setup(INPUT_PULLUP);
}

void loop() {
  upButton.update();
  downButton.update();
  if (upButton.isPushed()) {
    if (upButton.freeState == 0) {
      upButton.freeState = 1;
      targetValue += 100;
      if (targetValue > MAX_VALUE) {
        targetValue = MAX_VALUE;
      }
    }
  } else {
    upButton.freeState = 0;
  }

  if ( downButton.isPushed() ) {
    if (downButton.freeState == 0) {
      downButton.freeState = 1;
      targetValue -= 100;
      if (targetValue < 0) {
        targetValue = 0;
      }
    }
  } else {
    downButton.freeState = 0;
  }

  kitConnector.sendValue(targetValue);
  delay(30);
}

