int stato = 0;
int pin[7] = {2,3,4,5,6,7,8};
int face[7][7] = {
  {0,0,0,0,0,0,0},
  {0,0,0,1,0,0,0},
  {1,0,0,0,1,0,0},
  {1,0,0,1,1,0,0},
  {1,0,1,0,1,0,1},
  {1,0,1,1,1,0,1},
  {1,1,1,0,1,1,1}
};

void setup() {
  randomSeed(analogRead(A0));
  Serial.begin(9600);
  for (int i = 0; i < 7; i++) {
    pinMode(pin[i], OUTPUT);
  }
  pinMode(10, INPUT);
}
void loop() {
  switch (stato) {
  case 0:
    waitToStart();
    break;
  case 1:
    roll();
    break;
  case 2:
    display();
    break;
  }
}
void waitToStart() {
  if (digitalRead(10)) {
    stato = 1;
    delay(300);
  }
}

void roll() {
  int time = 50;
  for (int i = 0; i < 50; i++) {
    number(random(1, 7));
    delay(time);
    time = time + 20;
  }
  stato = 2;
}
void display() {
  //estraggo un numero a caso
  number(random(1, 7));
  stato = 0;
}
void number(int n) {
  for (int i = 0; i < 7; i++) {
    digitalWrite(pin[i], face[n][i]);
  }
}
