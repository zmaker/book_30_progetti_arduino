unsigned long t1, dt;
int pausa = 10;
void setup(void) {
  randomSeed(analogRead(A0));
  t1 = millis();
}
void loop(void) {
  dt = millis() - t1;
  if (dt > pausa) {
    pausa = random(1, 30);
    t1 = millis();
    int x = random(50,255);
    analogWrite(9, x);
} }
