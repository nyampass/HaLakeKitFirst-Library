#ifndef HaLakeKitFirst_h
#define HaLakeKitFirst_h

#include <Arduino.h>

#define HALAKEKITFIRST_BREAK_MILLIS 1000
#define HALAKEKITFIRST_SERIAL_SPEED 115200
#define HALAKEKITFIRST_MAX_VALUE 1023

class HaLakeKitFirst {
  public:
  HaLakeKitFirst(HardwareSerial* _hardSerial);
  void begin();
  bool receive(unsigned long breakMillis = (unsigned long) HALAKEKITFIRST_BREAK_MILLIS,
               bool clearBuffer = true);
  long sendValueInRange(long value, long min, long max);
  long getReceivedValueInRange(long min, long max);
  String getReceivedString();
  void clearSerialBuffer();

  private:
  String waitLine(unsigned long breakMillis);
  HardwareSerial* hardSerial;
  String receivedString;
};

#endif
