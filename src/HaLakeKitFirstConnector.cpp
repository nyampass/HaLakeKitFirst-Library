#include "HaLakeKitFirstConnector.h"

HaLakeKitFirstConnector::HaLakeKitFirstConnector(HardwareSerial* _hardSerial) {
  hardSerial = _hardSerial;
  breakMillis = (unsigned long) HALAKEKITFIRST_BREAK_MILLIS;
}

void HaLakeKitFirstConnector::begin() {
  hardSerial->begin(HALAKEKITFIRST_SERIAL_SPEED);
}

void HaLakeKitFirstConnector::setBreakMillis(unsigned long _breakMillis) {
  breakMillis = _breakMillis;
}

void HaLakeKitFirstConnector::sendValue(int value) {
  hardSerial->print("v ");
  hardSerial->print(value);
  hardSerial->print("\n");
}

static int HaLakeKitFirstConnector::valueFromLine(String line) {
  int spaceIndex = line.indexOf(' ');
  int errorValue = -1;
  String command = line.substring(0, spaceIndex);
  if (command != "v") {
    return errorValue;
  }

  String strValue = line.substring(spaceIndex + 1, line.length());
  if (strValue == "0") {
    return 0;
  }

  int intValue = strValue.toInt();
  if (intValue == 0) {
    return errorValue;
  } else {
    return intValue;
  }
}

void HaLakeKitFirstConnector::clearSerialBuffer() {
  while (hardSerial->available() > 0) {
    hardSerial->read();
  }
  return;
}

String HaLakeKitFirstConnector::waitLine(bool clearBuffer) {
  unsigned long waitTill = millis() + breakMillis;
  String receivedStr;
  char receivedChar;

  if (!clearBuffer) {
    clearSerialBuffer();
  }

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
