#include <SoftwareSerial.h>

#define SOFTRX 10
#define SOFTTX 11
SoftwareSerial SerialS(SOFTRX, SOFTTX);
void setup() {
  SerialS.begin(9600);
  pinMode(13, OUTPUT);
  delay(3000);
}
void loop() {
  if (SerialS.available()) {
    char ch = SerialS.read();
    //ricevo un carattere dalla seriale software e lo analizzo
    switch (ch) {
    case '0':
      blink(0);
      break;
    case '1':
      blink(1);
      break;
    case '2':
      blink(2);
      break;
    case '3':
      blink(3);
      break;
    }
  }
}

void blink(int n) {
  for (int i = 0; i < n + 1; i++) {
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
    delay(100);
  }
}
