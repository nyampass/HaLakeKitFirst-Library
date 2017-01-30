# HaLakeKitFirst
An arduino library to communicate serial in HaLakeKitFirst style.

# Install
You can install by using library manager.

[Sketch] -> [Include Library] -> [Manage Libraries..] -> search "halakekitfirst" then install it.

# Useage
If you want to get some sample, see [examples](/examples) of this project.

## Definition
```c
#ifdef USBCOM
// For Arduino Leonardo ets.. that its Serial is only for USB communication.
HaLakeKirFirst kitFirst(&Serial1);
#else
// For Arduino UNO etc..
HaLakeKitFirst kitFirst(&Serial);
#endif

void setup() {
  kitFirst.begin();
}
```

## Send
```c
int value = analogRead(SOME_PIN);
kitFirst.send(value,
              0,   // min value to send
              1023); // max value to send
```

## Receive
```c
int value;
if (kitFirst.receive()) {
  value = kitFirst.getReceivedValue(0,
                                    255);
}
analogWrite(SOME_PIN, value);
```
