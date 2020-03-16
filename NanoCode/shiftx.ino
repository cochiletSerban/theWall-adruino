#include <HC595.h>

const int chipCount = 4;  // Number of serialy connected 74HC595 (8 maximum)
const int latchPin = 4;  // Pin ST_CP (12) of the 74HC595
const int clockPin = 6;  // Pin SH_CP (11) of the 74HC595
const int dataPin = 4;   // Pin DS (14) of the 74HC595

//Constructor
HC595 ledArray(chipCount,latchPin,clockPin,dataPin);

int delayMs = 30;
int lastPin = ledArray.lastPin();

void setup() {
  ledArray.reset();
  ledArray.setPin(31, ON);
}

void loop() {}