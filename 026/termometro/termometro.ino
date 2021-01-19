#include <SimpleDHT.h>

#include "TM1637.h"

#define CLK 2
#define DIO 3
TM1637 tm1637(CLK, DIO);
SimpleDHT22 dht22(9);
void setup() {
  tm1637.init();
  tm1637.set(BRIGHT_TYPICAL);
}
void loop() {
  byte tt = 0; //temperatura
  byte hh = 0; //umidità
  dht22.read( & tt, & hh, NULL);
  shownumber(tt);
  delay(1000);
  shownumber(hh);
  delay(1000);
}

void shownumber(int n) {
  int u = n % 10;
  int d = (n / 10) % 10;
  int c = (n / 100) % 10;
  int m = (n / 1000) % 10;
  tm1637.display(0, m);
  tm1637.display(1, c);
  tm1637.display(2, d);
  tm1637.display(3, u);
}
