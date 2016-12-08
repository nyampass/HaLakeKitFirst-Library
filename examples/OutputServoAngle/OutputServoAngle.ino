#include "HaLakeKitFirstConnector.h"
#include <Servo.h>

#define SERVO_PIN 10

HaLakeKitFirstConnector kitConnector(&Serial);

Servo servo;
String receivedLine;
int receivedValue;
int microSec;

void setup() {
  kitConnector.begin();
}

void loop() {
  receivedLine = kitConnector.waitLine();
  receivedValue = kitConnector.valueFromLine(receivedLine);

  if (receivedValue > 0) {
    if (!servo.attached()) {
      servo.attach(SERVO_PIN);
    }
    // 1500 is middle
    microSec = map(receivedValue, 0, 1023, 600, 2400);
    servo.writeMicroseconds(microSec);
  } else {
    servo.detach();
  }
}
