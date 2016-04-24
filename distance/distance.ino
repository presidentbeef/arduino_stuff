/*
 * Car distance sensor
 */

int trig1 = 12;
int trig2 = 4;
int echo1 = 8;
int echo2 = 2;
int sound = 6;
int light1 = 13;
int light2 = 7;

int Parked = 0;
int Missing = 1;
int Nearby = 2;
int TooClose = 3;
int carStatus = Parked;

void setup() {
  pinMode(trig1, OUTPUT);
  pinMode(trig2, OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(echo2, INPUT);
  pinMode(sound, OUTPUT);
  pinMode(light1, OUTPUT);
  pinMode(light2, OUTPUT);
  Serial.begin(9600);
}

void sendTrigger(int trig) {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
}

int readDistance(int echo) {
  unsigned long duration = pulseIn(echo, HIGH);
  return (duration / 2) / 20.1;
}

void alert(int distance) {
  Serial.println(distance);
  if(distance < 40) {
    digitalWrite(light1, HIGH);
    digitalWrite(light2, HIGH);
    tone(sound, 524);
  }
  else if(distance < 60) {
    digitalWrite(light1, HIGH);
    tone(sound, 262);
  }
  else {
    digitalWrite(light1, LOW);
    digitalWrite(light2, LOW);
    noTone(sound);
  }
}

void checkDistance(int trig, int echo) {
  sendTrigger(trig);
  alert(readDistance(echo));
}

void loop() {
  checkDistance(trig1, echo1);
  delay(250);
  checkDistance(trig2, echo2);
  delay(250);
}
