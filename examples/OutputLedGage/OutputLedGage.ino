#include "HaLakeKitFirst.h"

const int LEVEL_PINS[] = {
  12,
  11,
  10,
  9,
  8,
  7,
  6,
  5,
  4,
  3
};
const int MAX_LEVEL = sizeof(LEVEL_PINS) / sizeof(int);

int currentLevel = 0;
int targetLevel;
int i;

HaLakeKitFirst kitFirst(&Serial);

void setup() {
  kitFirst.begin();

  for (i = 0; i < MAX_LEVEL; i++) {
    pinMode(LEVEL_PINS[i], OUTPUT);
  }

  updateDisplay(currentLevel);
}

void loop() {
  if (kitFirst.receive()) {
    targetLevel = kitFirst.getReceivedValue(0, MAX_LEVEL);
  }

  if (currentLevel != targetLevel) {
    currentLevel = targetLevel;
    updateDisplay(currentLevel);
  }
}

void updateDisplay(int level) {
  for (i = 0; i < MAX_LEVEL; i++) {
    if (level == 0) {
      if (i == 0) {
        setLevelPin(i, true);
      } else {
        setLevelPin(i, false);
      }
    } else {
      if (i == 0) {
        setLevelPin(i, false);
      } else if (i <= level) {
        setLevelPin(i, true);
      } else {
        setLevelPin(i, false);
      }
    }
  }
}

void setLevelPin(int num, bool value) {
  if (value) {
    digitalWrite(LEVEL_PINS[num], LOW);
  } else {
    digitalWrite(LEVEL_PINS[num], HIGH);
  }
}

