#include "HaLakeKitFirst.h"
#include <Servo.h>

#define SERVO_PIN 10
#define SERVO_MIN_MICROSEC 600
#define SERVO_MAX_MICROSEC 2400

HaLakeKitFirst kitFirst(&Serial);

Servo servo;
int microSec;

void setup() {
  kitFirst.begin();
}

void loop() {
  if (kitFirst.receive()) {
    if (!servo.attached()) {
      servo.attach(SERVO_PIN);
    }
    microSec =
      kitFirst.getReceivedValue(SERVO_MIN_MICROSEC,
                                       SERVO_MAX_MICROSEC);
    servo.writeMicroseconds(microSec);
  } else {
    servo.detach();
  }
}
