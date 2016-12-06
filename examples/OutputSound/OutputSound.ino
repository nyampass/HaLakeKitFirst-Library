#include "HaLakeKitFirstConnector.h"
#define SPEAKER_PIN 9

// https://www.arduino.cc/en/Reference/Tone
#define MIN_FREQUENCY 100
#define MAX_FREQUENCY 1500

HaLakeKitFirstConnector kitConnector(&Serial);

String kitStr;
int receivedValue;

int soundFrequency;

void setup() {
  kitConnector.begin();
  pinMode(SPEAKER_PIN, OUTPUT);
}

void loop() {
  kitStr = kitConnector.waitLine();
  receivedValue = kitConnector.valueFromLine(kitStr);

  if (receivedValue < 0) {
    soundFrequency = 0;
  } else {
    soundFrequency = map(receivedValue, 0, 1023, MIN_FREQUENCY, MAX_FREQUENCY);
  }

  tone(SPEAKER_PIN, soundFrequency, 100);
  delay(1);
}
