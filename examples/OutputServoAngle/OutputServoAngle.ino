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
    // 700 to 2300
    microSec = (receivedValue * 1.6) + 700;
    servo.writeMicroseconds(microSec);
  } else {
    servo.detach();
  }
}
