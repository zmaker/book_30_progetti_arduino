#include <Arduino.h>

#include <U8g2lib.h>

#include <Wire.h>

//Il parametro U8G2_R2 specifica la rotazione dello schermo
//U8G2_R0 per 0°, U8G2_R2 per 180°
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R2, SCL, SDA, U8X8_PIN_NONE);
int xship = 64;
int yship = 60;
int xshoot;
int yshoot;
bool FIRING = false;
int xalien;
int yalien;
bool ALIEN = false;
bool BOOM = false;
unsigned long t1, dt;
int points = 0;
char pts[5];
void setup(void) {
  u8g2.begin();
  pinMode(6, INPUT);
  randomSeed(analogRead(A1));
  u8g2.setFont(u8g2_font_unifont_t_symbols);
}
void loop(void) {
  u8g2.clearBuffer(); //ripulisce il buffer dello schermo
  int v = analogRead(A0);
  xship = map(v, 0, 1024, 123, 5);
  //sparo:
  if (digitalRead(6) && !FIRING) {
    FIRING = true;
    xshoot = xship;
    yshoot = yship - 5;
  }
  //astronave
  u8g2.drawTriangle(xship - 5, yship, xship + 5, yship, xship, yship - 5);
  //missile
  if (FIRING) {
    u8g2.drawLine(xshoot, yshoot, xshoot, yshoot - 5);
    yshoot = yshoot - 3;
    if (yshoot <= 0) {
      FIRING = false;
    }
  }
  //alieno
  if ((random(100) > 60) && !ALIEN) {
    ALIEN = true;
    xalien = 0;
    yalien = random(10, 50);
  }
  if (ALIEN) {
    u8g2.drawGlyph(xalien, yalien, 0x2606);
    if (!BOOM) { //se esplode l'alieno si ferma
      xalien = xalien + 2;
    }
    if (xalien >= 127) {
      ALIEN = false;
    }
  }
  //collisione
  if (ALIEN && FIRING &&
    (xshoot >= xalien) && (xshoot <= xalien + 8) &&
    (yshoot - 5 <= yalien + 8) && (yshoot - 5 >= yalien)) {
    //ALIEN = false;
    BOOM = true;
    FIRING = false; //nasconde e ferma il missile
    t1 = millis();
  }
  //esplosione
  if (BOOM) {
    u8g2.drawCircle(xalien + 4, yalien - 4, 5, U8G2_DRAW_ALL);
    u8g2.drawCircle(xalien + 4, yalien - 4, 8, U8G2_DRAW_ALL);
    dt = millis() - t1;
    if (dt >= 1000) {
      BOOM = false;
      ALIEN = false; //riattiva la creazione degli alieni
      points++;
    }
  }
  //punteggio
  sprintf(pts, "%3d", points);
  u8g2.drawStr(1, 10, pts);
  u8g2.sendBuffer(); //trasferisce il buffer al display
  delay(50);
}
