#include "HaLakeKitFirst.h"

#define TRIG_PIN 2
#define ECHO_PIN 3

#ifdef USBCON
HaLakeKitFirst kitFirst(&Serial1);
#else
HaLakeKitFirst kitFirst(&Serial);
#endif

int sensorValue;
int outValue;

int i;
int sumSensorValue;
int sensorCm;
const int sumupNumberOfTimes = 2;

void setup() {
  kitFirst.begin();
  pinMode( ECHO_PIN, INPUT );
  pinMode( TRIG_PIN, OUTPUT );
}

void loop() {
  for (i=0; i< sumupNumberOfTimes; i++) {
    sumSensorValue += getSonarDistance();
    delay(10);
  }

  sensorValue = sumSensorValue / sumupNumberOfTimes;
  sumSensorValue = 0;

  outValue = map(sensorValue, 10, 60, 1023, 0);
  if (outValue < 0) {
    outValue = 0;
  } else if (outValue > 1023) {
    outValue = 1023;
  }
  kitFirst.sendValueInRange(sensorValue, 60, 10);
}

float getSonarDistance() {
  float duration = 0;
  float distance = 0;

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds( 10 );
  digitalWrite(TRIG_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  duration = duration / 2; // get harf distance
  distance = duration * 340 * 100 / 1000000; // carc with sound speed as 340m/s
  //Serial.print(distance);
  //Serial.println(" cm");
  return distance;
}
