#include <Wire.h>

#include <Adafruit_GFX.h>

#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET 4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, & Wire, OLED_RESET);

void setup() {
  Serial.begin(9600);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 inizializzazione fallita"));
    for (;;); //loop infinito: ci blocchiamo qui
  }
  //se è necessario ruotare il display, utilizzare:
  //display.setRotation(180);
  display.clearDisplay();
  axis();
  display.display();
}

int bordo = 5;
int x = bordo;
int y, prev_y;

void loop() {
  int var = analogRead(A0);
  y = map(var, 0, 1023, SCREEN_HEIGHT - bordo, bordo);
  
  if (x > bordo) {
    display.drawLine(x - 1, prev_y, x, y, WHITE);
  }
  
  prev_y = y;
  x++;
  if (x >= (SCREEN_WIDTH - bordo)) {
    x = bordo;
    display.clearDisplay();
    axis();
  }
  delay(100);
  display.display();
}

void axis() {
  display.drawLine(bordo, SCREEN_HEIGHT - bordo, bordo, bordo, WHITE);
  display.drawLine(bordo, SCREEN_HEIGHT - bordo, SCREEN_WIDTH - bordo, SCREEN_HEIGHT - bordo, WHITE);
}
