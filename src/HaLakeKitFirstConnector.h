#ifndef HaLakeKitFirstConnector_h
#define HaLakeKitFirstConnector_h

#include <Arduino.h>

#define HALAKEKITFIRST_BREAK_MILLIS 1000
#define HALAKEKITFIRST_SERIAL_SPEED 115200

class HaLakeKitFirstConnector {
  public:
  HaLakeKitFirstConnector(HardwareSerial* _hardSerial);
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
