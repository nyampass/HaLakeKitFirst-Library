#include "HaLakeKitFirst.h"
#define SPEAKER_PIN 9

// https://www.arduino.cc/en/Reference/Tone
#define MIN_FREQUENCY 100
#define MAX_FREQUENCY 1000

HaLakeKitFirst kitFirst(&Serial);

int soundFrequency;

void setup() {
  kitFirst.begin();
  pinMode(SPEAKER_PIN, OUTPUT);
}

void loop() {
  if (kitFirst.receive()) {
    soundFrequency =
      kitFirst.getReceivedValueInRange(MIN_FREQUENCY,
                                       MAX_FREQUENCY);
  } else {
    soundFrequency = 0;
  }

  tone(SPEAKER_PIN, soundFrequency, 100);
  delay(1);
}
