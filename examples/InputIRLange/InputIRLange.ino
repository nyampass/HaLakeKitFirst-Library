#include "HaLakeKitFirst.h"

#define SENSOR_PIN 0

HaLakeKitFirst kitFirst(&Serial);

int sensorValue;

int i;
int sumSensorValue;
int sensorCm;
static int sumupNumberOfTimes = 5;

void setup() {
  kitFirst.begin();
  pinMode(SENSOR_PIN, INPUT);
}

void loop() {
  for (i=0; i< sumupNumberOfTimes; i++) {
    sumSensorValue += analogRead(SENSOR_PIN);
    delay(10);
  }

  sensorValue = sumSensorValue / sumupNumberOfTimes;
  sumSensorValue = 0;

  kitFirst.sendValue(sensorValue, 100, 400);
}

int partValueToCm(int value) {
  if (value < 200) {
    return 30;
  } else if (400 > value && value >= 200) {
    return map(value, 200, 400, 30, 13);
  } else if (600 > value && value >= 400) {
    return map(value, 400, 600, 13, 5);
  } else {
    return 5;
  }
}

int valueToCm(int value) {
  if (value < 100) {
    return 80;
  } else if (200 > value && value >=100) {
    return map(value, 100, 200, 80, 27);
  } else if (300 > value && value >= 200) {
    return map(value, 200, 300, 27, 17);
  } else if (400 > value && value >= 300) {
    return map(value, 300, 400, 17, 13);
  } else if (600 > value && value >= 400) {
    return map(value, 400, 600, 13, 5);
  } else {
    return 5;
  }
}
