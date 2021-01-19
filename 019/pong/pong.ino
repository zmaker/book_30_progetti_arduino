#include <Wire.h>

#include <Adafruit_GFX.h>

#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET - 1 // Reset pin -1 se non presente
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, & Wire, OLED_RESET);

int p1 = 0;
int lives = 3;

void setup() {
  Serial.begin(9600);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 non configurato"));
    for (;;);
  }
  display.display();
  display.clearDisplay();
  randomSeed(A2);
}

int x = 50;
int y = 50;
int incx = 1;
int incy = 1;
int padw = 30;
int padx = (display.width() + padw) / 2;

void loop() {
  display.clearDisplay();
  //pad
  padx = analogRead(A0);
  padx = map(padx, 0, 1024, 0, display.width() - padw);
  display.fillRect(padx, display.height() - 10, padw, 5, INVERSE);
  //palla
  display.fillRect(x, y, 5, 5, INVERSE);
  //aggiorna i punteggi
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(10, 0);
  display.println(lives);
  display.setCursor(70, 0);
  display.println(p1);
  //collisioni
  if (y > (display.height() - 15)) {
    //tocca il pad
    if ((x > padx) && (x < padx + padw - 5)) {
      incy = -incy;
    }
  }
  //tocca il fondo
  if (y >= (display.height() - 5)) {
    lives--;
    //riposiziona la palla a caso
    x = random(10, display.width() - 10);
    y = 10;
    delay(1000);
    if (lives == -1) {
      //game over
      while (1);
    }
  }
  //movimento della palla
  x = x + incx;
  if ((x > display.width() - 5) || (x < 0)) {
    incx = -incx;
  }
  y = y + incy;
  if ((y > display.height() - 5) || (y < 0)) {
    incy = -incy;
  }
  //tocca la cima
  if ((incy > 0) && (y == 0)) p1++;
  //aggiorna il disoplay
  display.display();
  delay(10);
}
