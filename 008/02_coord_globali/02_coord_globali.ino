#include "LedControl.h"

#define pinCLK 4
#define pinCS 3
#define pinDIN 2
#define ELEMENTS 8
LedControl lc = LedControl(pinDIN, pinCLK, pinCS, ELEMENTS);
void setup() {
  Serial.begin(9600);
  for (int i = 0; i < ELEMENTS; i++) {
    lc.shutdown(i, false); // Wake up displays
    lc.setIntensity(i, 1);
    lc.clearDisplay(i);
  }
}
void loop() {
  for (int y = 0; y < 8; y++) {
    for (int x = 0; x < 64; x++) {
      pixel(x, y, true);
      delay(10);
      pixel(x, y, false);
      delay(10);
    }
  }
}
void pixel(int x, int y, bool stato) {
  int el = (int)(x / 8);
  int xloc = 7 - (x - (8 * el));
  y = 7 - y;
  lc.setLed(el, y, xloc, stato);
}
