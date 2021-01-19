#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET - 1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, & Wire, OLED_RESET);

void setup() {
  Serial.begin(9600);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Indirizzo del display: 0x3C
    Serial.println(F("Errore sul display SSD1306 "));
    for (;;); //blocco lo sketch
  }
  display.display();
  display.clearDisplay();
}

float rx, v1 = 0;
float r1 = 1000; //1kohm resistenza nota

void loop() {
  int n = analogRead(A0);
  v1 = map(n, 0, 1023, 0, 5000) / 1000.0; //mV
  rx = (r1 * (5.0 - v1)) / v1;
  /*
  Serial.print(n);
  Serial.print("\t");
  Serial.print(v1);
  Serial.print("\t");
  Serial.println(rx);
  */
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  if (rx > 1000) {
    rx = rx / 1000.0;
    display.print(rx);
    display.print("K");
  } else {
    display.print(rx);
    display.print("R");
  }
  display.display();
  delay(200);
}
