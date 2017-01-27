#ifndef HaLakeKitFirst_h
#define HaLakeKitFirst_h

#include <Arduino.h>

#define HALAKEKITFIRST_BREAK_MILLIS 1000
#define HALAKEKITFIRST_SERIAL_SPEED 115200

class HaLakeKitFirst {
  public:
  HaLakeKitFirst(HardwareSerial* _hardSerial);
  void begin();
  void setBreakMillis(unsigned long _breakMillis);
  void sendValue(int value);
  void clearSerialBuffer();
  String waitLine(bool clearBuffer = true);

  static int valueFromLine(String line);

  private:
  HardwareSerial* hardSerial;
  unsigned long breakMillis;
};

#endif
