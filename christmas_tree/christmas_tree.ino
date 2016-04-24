/*
 * Christmas tree circuit
 */

int trig = 12;
int echo = 13;

void setup() {
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  //Serial.begin(9600);
}

void clear_lights() {
  digitalWrite(2, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(9, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(11, LOW);
}

void light_up(int d) {
  clear_lights();

  delay(d);
  digitalWrite(11, HIGH);
  delay(d);
  digitalWrite(8, HIGH);
  delay(d);
  digitalWrite(7, HIGH);
  delay(d);
  digitalWrite(4, HIGH);
  delay(d);
  digitalWrite(2, HIGH);
  delay(d);
  showRGB(708);
  delay(d*2);
}

void light_down(int d) {
  clear_lights();

  delay(d);
  showRGB(708);
  delay(d);
  digitalWrite(2, HIGH);
  delay(d);
  digitalWrite(4, HIGH);
  delay(d);
  digitalWrite(7, HIGH);
  delay(d);
  digitalWrite(8, HIGH);
  delay(d);
  digitalWrite(11, HIGH);
  delay(d*2);
}

void dark_down(int d) {
  delay(d);
  topper(0, 0, 0);
  delay(d);
  digitalWrite(2, LOW);
  delay(d);
  digitalWrite(4, LOW);
  delay(d);
  digitalWrite(7, LOW);
  delay(d);
  digitalWrite(8, LOW);
  delay(d);
  digitalWrite(11, LOW);
  delay(d*2);
}

void topper(int r, int g, int b) {
  analogWrite(5, r % 256);
  analogWrite(3, g % 256);
  analogWrite(9, b % 256);
}

void sendTrigger(int trig) {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
}

int checkDistance() {
  sendTrigger(trig);
  readDistance(echo);
}

int readDistance(int echo) {
  unsigned long duration = pulseIn(echo, HIGH);
  return (duration / 2) / 20.1;
}

void showRGB(int color)
{
  int redIntensity;
  int greenIntensity;
  int blueIntensity;

  // Obviously copied this from somewhere...
  //
  // Here we'll use an "if / else" statement to determine which
  // of the three (R,G,B) zones x falls into. Each of these zones
  // spans 255 because analogWrite() wants a number from 0 to 255.

  // In each of these zones, we'll calculate the brightness
  // for each of the red, green, and blue LEDs within the RGB LED.

  if (color <= 255)          // zone 1
  {
    redIntensity = 255 - color;    // red goes from on to off
    greenIntensity = color;        // green goes from off to on
    blueIntensity = 0;             // blue is always off
  }
  else if (color <= 511)     // zone 2
  {
    redIntensity = 0;                     // red is always off
    greenIntensity = 255 - (color - 256); // green on to off
    blueIntensity = (color - 256);        // blue off to on
  }
  else // color >= 512       // zone 3
  {
    redIntensity = (color - 512);         // red off to on
    greenIntensity = 0;                   // green is always off
    blueIntensity = 255 - (color - 512);  // blue on to off
  }

  topper(redIntensity, blueIntensity, greenIntensity);
}

void distance_stuff() {
  int d = 0; 
  while(d < 120 || d > 5000) {
    d = checkDistance();
    //Serial.println(d);
    showRGB(d * 3 % 768);
    delay(50);
  }
}

void wait_for_movement() {
  int i = 0;
  while(checkDistance() > 110 && i < 6000) {
    delay(10);
    i =i + 1;
  }
}

void loop() {
  light_up(125);
  distance_stuff();
  distance_stuff();
  wait_for_movement();
  delay(500);
  topper(0, 0, 0);
  dark_down(125);
  delay(500);
  light_down(125);
  distance_stuff();
  distance_stuff();
  wait_for_movement();
  delay(500);
  topper(0, 0, 0);
  dark_down(125);
}
