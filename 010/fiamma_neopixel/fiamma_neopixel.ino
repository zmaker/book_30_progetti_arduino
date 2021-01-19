#include <FastLED.h>

#define NLEDS 8

CRGB leds[NLEDS];

void setup() {
  clearleds();
  randomSeed(analogRead(A0));
}

int i, t = 0;
int r, b, g;

void loop() {
  t = random(5, 31);
  r = random(0, map(analogRead(A4), 0, 1023, 0, 255));
  g = random(0, map(analogRead(A5), 0, 1023, 0, 255));
  b = random(0, 33);
  leds[i] = CRGB(r, g, b);
  i++;
  if (i > NLEDS) i = 0;
  FastLED.show();
  delay(t);
}

void clearleds() {
  FastLED.addLeds < WS2812, 6, GRB > (leds, NLEDS);
  for (int i = 0; i < NLEDS; i++) {
    leds[i] = CRGB(0, 0, 0);
  }
  FastLED.show();
}
