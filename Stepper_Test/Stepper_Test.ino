const int stepPin = 2;
const int dirPin = 3;

void setup() {
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);

  digitalWrite(dirPin, HIGH);

}

void loop() {
  digitalWrite(stepPin, HIGH);
  delayMicroseconds(2.5);
  digitalWrite(stepPin, LOW);
  delayMicroseconds(3000);

}
