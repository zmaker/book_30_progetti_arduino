//HR04 Sensore ultrasuoni
const int triggerPort = 6;
const int echoPort = 7;
const int led = 13;
const int buzzer = 10;
#define MAXDIST 100
#define MINDIST 25
void setup() {
  pinMode(triggerPort, OUTPUT);
  pinMode(echoPort, INPUT);
  pinMode(led, OUTPUT);
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);
}
unsigned long t1, dt;
int tblink = 100;
int statoled = LOW;
int freq = 220;
void loop() {
  long distanza = misura();
  Serial.print("distanza: ");
  Serial.println(distanza);
  if (distanza < MINDIST) {
    digitalWrite(led, HIGH);
    tone(buzzer, 880);
  } else if (distanza > MAXDIST) {
    digitalWrite(led, LOW);
    noTone(buzzer);
  } else {
    tblink = map(distanza, MINDIST, MAXDIST, 100, 500);
    freq = map(distanza, MINDIST, MAXDIST, 880, 220);
    dt = millis() - t1;
    if (dt > tblink) {
      statoled = !statoled;
      digitalWrite(led, statoled);
      t1 = millis();
      if (statoled) {
        tone(buzzer, freq, 100);
      } else {
        //noTone(buzzer);
      }
    }
  }
  delay(100);
}
long misura() {
  //porta bassa l'uscita del trigger
  digitalWrite(triggerPort, LOW);
  //invia un impulso di 10microsec su trigger
  digitalWrite(triggerPort, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPort, LOW);
  long durata = pulseIn(echoPort, HIGH);
  long distanza = durata / 58.0f;
  return distanza;
}
