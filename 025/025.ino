#include <LiquidCrystal.h>

const int rs = 12,
  en = 11,
  d4 = 5,
  d5 = 4,
  d6 = 3,
  d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
void setup() {
  //imposto il numero di colonne e righe del display:
  lcd.begin(16, 2);
  //scrivo un messaggio all'accensione
  lcd.print("pH meter");
  delay(1000);
  lcd.setCursor(0, 1);
  lcd.print("pH=");
  delay(1000);
}
float prevph = 0;
void loop() {
  float m = misuraph();
  if (m != prevph) {
    lcd.setCursor(4, 1);
    lcd.print("        ");
    lcd.setCursor(4, 1);
    lcd.print(m);
    prevph = m;
  }
  delay(500);
}
float misuraph() {
  long misura = 0;
  for (int i = 0; i < 10; i++) {
    misura += analogRead(A0);
    delay(10);
  }
  int mm = misura / 10;
  float ph = ((float) mm * 5.0 f) / 1024.0 f;
  ph = 3.5 * ph;
  return ph;
}
