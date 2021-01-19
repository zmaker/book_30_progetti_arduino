#include <FastLED.h>

#define NUM_LEDS 50
CRGB leds[NUM_LEDS];
void setup() {
  FastLED.addLeds < WS2812, 6, GRB > (leds, NUM_LEDS);
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(0, 0, 0);
  }
  FastLED.show();
}
void loop() {
  for (int i = 1; i < NUM_LEDS; i++) {
    leds[i - 1] = CRGB(0, 0, 0);
    leds[i] = CRGB(255, 0, 0);
    FastLED.show();
    delay(50);
  }
  for (int i = NUM_LEDS-1; i > 0; i--) {
    leds[i] = CRGB(0, 0, 0);
    leds[i - 1] = CRGB(255, 0, 0);
    FastLED.show();
    delay(50);
  }
}
