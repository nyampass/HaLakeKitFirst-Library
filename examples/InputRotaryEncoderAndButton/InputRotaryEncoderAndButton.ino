#include <HaLakeKitFirst.h>
#include <MsTimer2.h>
#define ROTERY_PIN_A 10
#define ROTERY_PIN_B 9
#define SWITCH_PIN 8

HaLakeKitFirst kitConnector(&Serial);

volatile int roteryValue;

int currentValue;
int prevValue;
int isCountDowning;
int valueToSend;

void setup(void) {
  kitConnector.begin();
  pinMode(ROTERY_PIN_A, INPUT_PULLUP);
  pinMode(ROTERY_PIN_B, INPUT_PULLUP);
  pinMode(SWITCH_PIN, INPUT_PULLUP);

  MsTimer2::set(1, timerIRQ);
  MsTimer2::start();
}

void loop(void) {
  prevValue = currentValue;
  currentValue = roteryValue;

  if (prevValue != currentValue) {
    static int valueDiff;
    valueDiff = currentValue - prevValue;
    valueToSend = valueToSend + (32 * valueDiff);
  }

  // Count Down processes
  if (digitalRead(SWITCH_PIN) == LOW) {
    isCountDowning = true;
  }
  if (valueToSend <= 0) {
    isCountDowning = false;
  }
  if (isCountDowning) {
    valueToSend --;
  }

  valueToSend = constrain(valueToSend, 0, 1023);
  kitConnector.sendValue(valueToSend);
  delay(50);
}

// Reference
// http://radiopench.blog96.fc2.com/blog-entry-556.html

void timerIRQ() {
  static byte bp = 0;

  bp = bp << 1;
  if (digitalRead(ROTERY_PIN_A) == HIGH) {
    bp |= 0x01;
  }
  bp = bp << 1;
  if (digitalRead(ROTERY_PIN_B) == HIGH) {
    bp |= 0x01;
  }

  // remove top 4bits
  bp = bp & 0x0F;
  if (bp == 0b0111) {
  // if ((bp == 0b0111) | (bp == 0b1000)) {
    roteryValue ++;
  }
  if (bp == 0b1011) {
  // if ((bp == 0b1011) | (bp == 0b0100)) {
    roteryValue --;
  }
}
