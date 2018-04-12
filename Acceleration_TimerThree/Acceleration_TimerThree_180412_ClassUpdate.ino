#include <TimerThree.h>
//disables PWM on pins 11, 12, 13, but maybe also 2,3,5? Will have to figure out - just don't use PWM on them for now

const int stepPinA = 2;
const int dirPinA = 3;
const int stepPinB = 4;
const int dirPinB = 5;

volatile int dirA;
volatile float stepsPerSecA;
volatile boolean steppedA = false;
volatile float endingoffIntervalA;
volatile float offIntervalA;
volatile int callCounterA = 0;

volatile int dirB;
volatile float stepsPerSecB;
volatile boolean steppedB = false;
volatile float endingoffIntervalB;
volatile float offIntervalB;
volatile int callCounterB = 0;

float decrement = .025;
volatile float startingOffInterval = 250;
int interruptInterval = 5;

boolean reset = false;

void setup() {
  Serial.begin(2000000);

  pinMode(stepPinA, OUTPUT);
  pinMode(dirPinA, OUTPUT);
  pinMode(stepPinB, OUTPUT);
  pinMode(dirPinB, OUTPUT);

  Timer3.initialize(interruptInterval);
  Timer3.attachInterrupt(stepMotor);
}

void stepMotor() {
  switch (dirA) {
    case 0:                           //stopped
      digitalWrite(stepPinA, LOW);
      break;
    case 1:                           //forward
      //Serial.println("ForwardA");
      digitalWrite(dirPinA, HIGH);
      break;
    case -1:                          //backward
     //Serial.println("BackwardA");
      digitalWrite(dirPinA, LOW);
      break;
  }
  if (dirA == 1 ){
      if (steppedA) {
        digitalWrite(stepPinA, LOW);
        //Serial.println("Not steppingA");

        callCounterA = 0;
        steppedA = false;
      }
      else {
        if (offIntervalA - 1 >= endingoffIntervalA) {
          offIntervalA -= decrement;
          //  Serial.println(offIntervalA);
        }
        if (callCounterA >= offIntervalA) {
          digitalWrite(stepPinA, HIGH);          //step
          //Serial.println("StepA");
          steppedA = true;
        }
        else {
          callCounterA++;
          //Serial.println(callCounterA);
        }
      }
  }


   switch (dirB) {
    case 0:                           //stopped
      digitalWrite(stepPinB, LOW);
      break;
    case 1:                           //forward
      //Serial.println("ForwardB");
      digitalWrite(dirPinB, HIGH);
      break;
    case -1:                          //backward
     //Serial.println("BackwardB");
      digitalWrite(dirPinB, LOW);
      break;
  }
  if (dirB == 1 || dirB == -1){
      if (steppedB) {
        digitalWrite(stepPinB, LOW);
        //Serial.println("Not steppingB");

        callCounterB = 0;
        steppedB = false;
      }
      else {
        if (offIntervalB - 1 >= endingoffIntervalB) {
          offIntervalB -= decrement;
          //  Serial.println(offIntervalB);
        }
        if (callCounterB >= offIntervalB) {
          digitalWrite(stepPinB, HIGH);          //step
          //Serial.println("StepB");
          steppedB = true;
        }
        else {
          callCounterB++;
          //Serial.println(callCounterB);
        }
      }
  }
}
void loop() {
  forward(5000000);
//    delay(5000);
//    reset = false;
//    backward(400);
//    delay(5000);
//    reset = false;
//    Stop();
//    delay(750);
}
void forward(float speed_) {
  endingoffIntervalA = ((1 / stepsPerSecA) * 1000000) / interruptInterval;
  if (reset) {
    //run
    dirA = 1;
    stepsPerSecA = speed_;
    dirB = 1;
    stepsPerSecB = speed_;
  }
  else {
    offIntervalA = startingOffInterval;
    offIntervalB = startingOffInterval;
    reset = true;
  }
}
void backward(float speed_) {
  endingoffIntervalA = ((1 / stepsPerSecA) * 1000000) / interruptInterval;
  if (reset) {
    //run
    dirA = -1;
    stepsPerSecA = speed_;
    dirB = -1;
    stepsPerSecB = speed_;
  }
  else {
    offIntervalA = startingOffInterval;
    offIntervalB = startingOffInterval;
    reset = true;
  }
}
void Stop() {
  dirA = 0;
  dirB = 0;
}
void centerLeft(int speed_) {

}
void centerRight(int speed_) {

}
void curve(int speedLeft, int speedRight) {

}
