#include "HaLakeKitFirst.h"

#define MAX_LEVEL 9 // 0 to 9

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

int currentLevel = 0;
int targetLevel;
int i;

HaLakeKitFirst kitConnector(&Serial);

String kitStr;
int receivedValue;
int outValue;

void setup() {
  kitConnector.begin();

  for (i = 0; i < MAX_LEVEL + 1; i++) {
    pinMode(LEVEL_PINS[i], OUTPUT);
  }

  updateDisplay(currentLevel);
}

void loop() {
  kitStr = kitConnector.waitLine();
  receivedValue = kitConnector.valueFromLine(kitStr);

  if (receivedValue < 0) {
    targetLevel = 0;
  } else {
    targetLevel = receivedValue / 100;
  }
  if (targetLevel > MAX_LEVEL) {
    targetLevel = MAX_LEVEL;
  }

  if (currentLevel != targetLevel) {
    currentLevel = targetLevel;
    updateDisplay(currentLevel);
  }
}

void updateDisplay(int level) {
  for (i = 0; i < MAX_LEVEL + 1; i++) {
    if (level == 0) {
      if (i==0) {
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

