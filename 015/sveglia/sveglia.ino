#include <LiquidCrystal.h>

#define KY_NONE 0
#define KY_LEFT 1
#define KY_RIGHT 2
#define KY_UP 3
#define KY_DOWN 4
#define KY_SEL 5
#define TH_NONE 1023
#define TH_LEFT 409
#define TH_RIGHT 0
#define TH_UP 99
#define TH_DOWN 256
#define TH_SEL 640

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

int stato = 0;
int key;
int digit = 10;
unsigned long t1;
char str[16];
char caratteri[] {
  'a',
  'b',
  'c',
  'd',
  'e',
  'f',
  'g',
  'h',
  'i',
  'j',
  'k',
  'l',
  'm',
  'n',
  'o',
  'p',
  'q',
  'r',
  's',
  't',
  'u',
  'v',
  'x',
  'y',
  'z',
  '0',
  '1',
  '2',
  '3',
  '4',
  '5',
  '6',
  '7',
  '8',
  '9',
  '!',
  '*',
  '-'
};
String pass = "";

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  randomSeed(analogRead(A2));
}

void loop() {
  switch (stato) {
  case 0:
    stato_0();
    break;
  case 1:
    stato_1();
    break;
  case 2:
    stato_2();
    break;
  }
}
int readKeys() {
  int n = analogRead(A0);
  if ((n >= TH_LEFT - 5) && (n <= TH_LEFT + 5)) {
    return KY_LEFT;
  } else if ((n >= TH_RIGHT - 5) && (n <= TH_RIGHT + 5)) {
    return KY_RIGHT;
  } else if ((n >= TH_RIGHT - 5) && (n <= TH_RIGHT + 5)) {
    return KY_RIGHT;
  } else if ((n >= TH_UP - 5) && (n <= TH_UP + 5)) {
    return KY_UP;
  } else if ((n >= TH_DOWN - 5) && (n <= TH_DOWN + 5)) {
    return KY_DOWN;
  } else if ((n >= TH_SEL - 5) && (n <= TH_SEL + 5)) {
    return KY_SEL;
  } else return KY_NONE;
}
void stato_0() {
  switch (key) {
  case KY_SEL:
    stato = 1;
    t1 = millis();
    break;
  case KY_UP:
    digit++;
    delay(200);
    break;
  case KY_DOWN:
    digit--;
    delay(200);
    break;
  }
  digit = constrain(digit, 1, 12);
  if ((millis() - t1) > 100) {
    lcd.setCursor(0, 0);
    sprintf(str, "chars: %02d ", digit);
    lcd.print(str);
    t1 = millis();
  }
}
void stato_1() {
  //genero la password
  for (int i = 0; i < digit; i++) {
    int n = random(0, sizeof(caratteri));
    char ch = caratteri[n];
    pass += ch;
  }
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(pass);
  stato = 2;
}
void stato_2() {
  switch (key) {
  case KY_SEL:
    stato = 0;
    pass = "";
    t1 = millis();
    lcd.clear();
    delay(1000);
    break;
  }
}
