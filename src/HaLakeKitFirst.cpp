#include "HaLakeKitFirst.h"

long constrainAndMap(long value, long fromMin, long fromMax, long toMin, long toMax) {
  long constrainedValue =
    (fromMin < fromMax) ?
    constrain(value, fromMin, fromMax):
    constrain(value, fromMax, fromMin);
  return map(constrainedValue,
             fromMin,
             fromMax,
             toMin,
             toMax);
}

HaLakeKitFirst::HaLakeKitFirst(HardwareSerial* _hardSerial) {
  hardSerial = _hardSerial;
}

void HaLakeKitFirst::begin() {
  hardSerial->begin(HALAKEKITFIRST_SERIAL_SPEED);
}

long HaLakeKitFirst::sendValueInRange(long value, long min, long max) {
  long valueToSend = constrainAndMap(value,
                                     min,
                                     max,
                                     0,
                                     HALAKEKITFIRST_MAX_VALUE);
  hardSerial->print("v ");
  hardSerial->print(valueToSend);
  hardSerial->print("\n");
  return valueToSend;
}

long HaLakeKitFirst::getReceivedValueInRange(long min, long max) {
  int spaceIndex = receivedString.indexOf(' ');
  String command = receivedString.substring(0, spaceIndex);
  if (command != "v") {
    return min;
  }

  String strValue = receivedString.substring(spaceIndex + 1, receivedString.length());
  return constrainAndMap(strValue.toInt(),
                         0,
                         HALAKEKITFIRST_MAX_VALUE,
                         min,
                         max);
}

void HaLakeKitFirst::clearSerialBuffer() {
  while (hardSerial->available() > 0) {
    hardSerial->read();
  }
  return;
}

bool HaLakeKitFirst::receive(unsigned long breakMillis, bool clearBuffer) {
  if (!clearBuffer) {
    clearSerialBuffer();
  }
  receivedString = waitLine(breakMillis);
  return receivedString.length() > 0;
}

String HaLakeKitFirst::waitLine(unsigned long breakMillis) {
  unsigned long waitTill = millis() + breakMillis;
  String receivedStr;
  char receivedChar;

  while (receivedStr.length() == 0 && waitTill > millis()) {
    while (hardSerial->available() > 0) {
      receivedChar = (char)hardSerial->read();
      if (receivedChar == "\n") {
        break;
      } else {
        receivedStr.concat(receivedChar);
        delay(2);
      }
    }
  }

  // remove return or feed character
  int lastCharIndex = receivedStr.length() -1;
  while(receivedStr[lastCharIndex] == '\n' || receivedStr[lastCharIndex] == '\r') {
    receivedStr.remove(lastCharIndex);
    lastCharIndex --;
  }

  return receivedStr;
}
