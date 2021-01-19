#include <Servo.h>

#include <Wire.h>

#include <Adafruit_GFX.h>

#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET - 1 // Reset pin # (-1 se non presente)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, & Wire, OLED_RESET);

Servo myservo;
int Echo = 8;
int Trig = 9;

void setup() {
  myservo.attach(3);
  Serial.begin(9600);
  pinMode(Echo, INPUT);
  pinMode(Trig, OUTPUT);
  Serial.println("Ok");
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 non trovato / errori di connessione!"));
    for (;;); // si blocca qui
  }
  display.display(); //visualizza la splash screen (se presente)
  display.clearDisplay(); //pulisce lo schermo
}

void loop() {
  Serial.println("Scan");
  display.clearDisplay();
  myservo.write(90);
  for (int i = 30; i < 150; i = i + 5) {
    myservo.write(i);
    int d = readDistanza();
    d = map(d, 0, 100, 0, 60);
    float a = PI * (float) i / 180.0f;
    int xl = 64 - cos(a) * d;
    int yl = 10 + sin(a) * d;
    display.drawLine(64, 10, xl, yl, WHITE);
    display.display();
    Serial.println(d);
    delay(100);
  }
  myservo.write(90);
  delay(500);
}

int readDistanza() {
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(20);
  digitalWrite(Trig, LOW);
  float d = pulseIn(Echo, HIGH);
  d = d / 58;
  return (int) d;
}
