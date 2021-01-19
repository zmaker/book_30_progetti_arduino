int redPin = 6;
int greenPin = 5;
int bluePin = 3;
float col[3];
float hue = 0.0;
void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}
void loop() {
  setColor(hsv2rgb(hue, 1.0, 1.0, col));
  delay(50);
  hue += 0.01;
  if (hue >= 1.0) hue = 0.0;
}
void setColor(float * rgb) {
  analogWrite(redPin, (int)((1.0 - rgb[0]) * 255));
  analogWrite(greenPin, (int)((1.0 - rgb[1]) * 255));
  analogWrite(bluePin, (int)((1.0 - rgb[2]) * 255));
}
// HSV->RGB conversion based on GLSL version
// expects hsv channels defined in 0.0 .. 1.0 interval
float fract(float x) {
  return x - int(x);
}
float mix(float a, float b, float t) {
  return a + (b - a) * t;
}
float step(float e, float x) {
  return x < e ? 0.0 : 1.0;
}
float * hsv2rgb(float h, float s, float b, float * rgb) {
  rgb[0] = b * mix(1.0, constrain(abs(fract(h + 1.0) * 6.0 - 3.0) - 1.0, 0.0, 1.0), s);
  rgb[1] = b * mix(1.0, constrain(abs(fract(h + 0.6666666) * 6.0 - 3.0) - 1.0, 0.0,
    1.0), s);
  rgb[2] = b * mix(1.0, constrain(abs(fract(h + 0.3333333) * 6.0 - 3.0) - 1.0, 0.0,
    1.0), s);
  return rgb;
}
