#include <SoftwareSerial.h>

#include <Adafruit_Fingerprint.h>

SoftwareSerial mySerial(2, 3); //RX, TX
Adafruit_Fingerprint finger = Adafruit_Fingerprint( & mySerial);
void setup() {
  Serial.begin(9600);
  finger.begin(57600);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  Serial.println("pronto");
}
void loop() {
  int id = getFingerprintID();
  if (id == 1) {
    Serial.println("ON");
    digitalWrite(12, HIGH);
    digitalWrite(11, HIGH); //rele
    delay(3000);
    digitalWrite(12, LOW);
    digitalWrite(11, LOW); //rele
  } else {
    Serial.println("???");
    digitalWrite(13, HIGH);
    delay(3000);
    digitalWrite(13, LOW);
  }
  delay(50);
}

uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  if (p == FINGERPRINT_OK) {
    p = finger.image2Tz();
    if (p == FINGERPRINT_OK) {
      p = finger.fingerSearch();
      if (p == FINGERPRINT_OK) {
        Serial.print("Found ID #");
        Serial.print(finger.fingerID);
        Serial.print(" with confidence of ");
        Serial.println(finger.confidence);
        return finger.fingerID;
      }
    }
  }
  return -1;
}
