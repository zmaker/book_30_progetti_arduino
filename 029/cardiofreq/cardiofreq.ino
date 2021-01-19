#include <Wire.h>

#include <Adafruit_GFX.h>

#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET 4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, & Wire, OLED_RESET);
static
const unsigned char PROGMEM icona[] = {
  B00000000,
  B00110110,
  B01111111,
  B01111111,
  B00111110,
  B00011100,
  B00001000,
  B00000000
};
int n;
float reader;
unsigned long start;
#define samp_siz 4
float reads[samp_siz];
float sum, last;
unsigned long ptr;
float before;
#define rise_threshold 5
bool rising;
int rise_count;
float first, second, third, print_value;
unsigned long last_beat;
void setup() {
  pinMode(13, OUTPUT);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  display.clearDisplay();
}
void loop() {
  n = 0;
  start = millis();
  reader = 0;
  //questo ciclo bloccante calcola il valor medio in 20ms
  do {
    reader += analogRead(A0);
    n++;
  } while (millis() < start + 20);
  reader = reader / n; // il valor medio
  sum -= reads[ptr];
  sum += reader;
  reads[ptr] = reader;
  last = sum / samp_siz;
  // verifichiamo se abbiamo una curva ascendente
  if (last > before) {
    rise_count++;
    if (!rising && rise_count > rise_threshold) {
      rising = true;
      first = millis() - last_beat;
      last_beat = millis();
      print_value = 60000. / (0.4 * first + 0.3 * second + 0.3 * third);
      third = second;
      second = first;
      digitalWrite(13, HIGH);
      printoled(print_value, true);
    } else {
      digitalWrite(13, LOW);
      printoled(print_value, false);
    }
  } else {
    // curva discendente
    rising = false;
    rise_count = 0;
  }
  before = last;
  ptr++;
  ptr %= samp_siz;
}
void printoled(int val, bool icon) {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(10, 10);
  display.print(val);
  if (icon) {
    display.drawBitmap(100, 10, icona, 8, 8, 1);
  }
  display.display();
}
