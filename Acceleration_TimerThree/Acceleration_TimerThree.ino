#include <TimerThree.h>
//disables PWM on pins 11, 12, 13, but maybe also 2,3,5? Will have to figure out - just don't use PWM on them for now

const int stepPin = 2;
const int dirPin = 3;
volatile int dir;
volatile float stepsPerSec;
volatile boolean stepped = false;
volatile float startingOffInterval = 250;
volatile float offInterval;
volatile int callCounter = 0;
volatile int decrement = 0;
int interruptInterval = 5;

boolean reset = false;

void setup() {
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);

  Timer3.initialize(interruptInterval);
  Timer3.attachInterrupt(stepMotor);
}

void stepMotor() {
  switch (dir) {
    case 0:                           //stopped
      digitalWrite(stepPin, LOW);
      break;
    case 1;                           //forward
      float endingOffInterval = ((1 / stepsPerSec) * 1000000) / interruptInterval;

      digitalWrite(dirPin, HIGH);

      if (stepped) {
        digitalWrite(stepPin, LOW);
        
        callCounter = 0;
        if (offInterval - 1 >= endingOffInterval) {
          offInterval--;
        }
        stepped = false;
      }
      else {
        if (callCounter >= offInterval) {
          digitalWrite(stepPin, HIGH);          //step
          stepped = true;
        }
        else {
          callCounter++;
        }
      }
      break;
    case -1:                          //backward
      float endingOffInterval = ((1 / stepsPerSec) * 1000000) / interruptInterval;

      digitalWrite(dirPin, LOW);

      if (stepped) {
        digitalWrite(stepPin, LOW);
        
        callCounter = 0;
        if (offInterval - 1 >= endingOffInterval) {
          offInterval--;
        }
        stepped = false;
      }
      else {
        if (callCounter >= offInterval) {
          digitalWrite(stepPin, HIGH);          //step
          stepped = true;
        }
        else {
          callCounter++;
        }
      }
      break;
  }
}

void loop() {
  forward(400);
  delay(5000);
  reset = false;
  backward(400);
  delay(5000);
  reset = false;
  Stop();
  delay(750);
}
void forward(float speed_) {
  if (reset) {
    //run
    dir = 1;
    stepsPerSec = speed_;
  }
  else {
    offInterval = startingOffInterval;
    reset = true;
  }
}
void forward(float speed_) {
  if (reset) {
    //run
    dir = -1;
    stepsPerSec = speed_;
  }
  else {
    offInterval = startingOffInterval;
    reset = true;
  }
}
void Stop() {
  dir = 0;
}

