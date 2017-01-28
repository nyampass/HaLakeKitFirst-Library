#include "HaLakeKitFirst.h"
#include "PushButton.h"

#define UP_BUTTON_PIN 2
#define DOWN_BUTTON_PIN A0
#define BUTTON_CHANGE_VALUE 100

HaLakeKitFirst kitFirst(&Serial);

int targetValue = 0;
PushButton upButton(UP_BUTTON_PIN, LOW);
PushButton downButton(DOWN_BUTTON_PIN, LOW);

void setup() {
  kitFirst.begin();

  upButton.setup(INPUT_PULLUP);
  downButton.setup(INPUT_PULLUP);
}

void loop() {
  upButton.update();
  downButton.update();
  if (upButton.isPushed()) {
    if (upButton.freeState == 0) {
      upButton.freeState = 1;
      targetValue += BUTTON_CHANGE_VALUE;
    }
  } else {
    upButton.freeState = 0;
  }

  if ( downButton.isPushed() ) {
    if (downButton.freeState == 0) {
      downButton.freeState = 1;
      targetValue -= BUTTON_CHANGE_VALUE;
    }
  } else {
    downButton.freeState = 0;
  }

  targetValue = kitFirst.sendValueInRange(targetValue, 0, HALAKEKITFIRST_MAX_VALUE);
  delay(30);
}

