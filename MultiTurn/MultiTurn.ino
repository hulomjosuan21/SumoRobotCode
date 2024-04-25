#include <Arduino.h>
#define MAX_DISTANCE 12
// Hulom's Group
const int PWMA = 5;
const int PWMB = 5;
const int AIN1 = 4;
const int AIN2 = 6;
const int BIN1 = 3;
const int BIN2 = 2;

const int moveForwardSpeed = 100;
const int moveBackwardSpeed = 150;
const int motorTurnSpeed = 150;

const int left_Trig = 8;
const int left_Echo = 9;
const int right_Trig = 10;
const int right_Echo = 11;

const int left_IR = 12; 
const int Right_IR = 13; 
const int back_IR = 7;

void setup() {
  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);

  pinMode(left_Trig, OUTPUT);
  pinMode(right_Trig, OUTPUT);
  
  pinMode(left_Echo, INPUT);
  pinMode(right_Echo, INPUT);

  pinMode(left_IR, INPUT);
  pinMode(Right_IR, INPUT);
  pinMode(back_IR, INPUT);

  Serial.begin(9600);
}

void moveForward() {
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
  analogWrite(PWMA, moveForwardSpeed);
  analogWrite(PWMB, moveForwardSpeed);
}

void moveBackward() {
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);
  analogWrite(PWMA, moveBackwardSpeed);
  analogWrite(PWMB, moveBackwardSpeed);
}

void stopMotors() {
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, LOW);
  analogWrite(PWMA, 0);
  analogWrite(PWMB, 0);
}

void leftTurn() {
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
  analogWrite(PWMA, motorTurnSpeed);
  analogWrite(PWMB, motorTurnSpeed);
}

void rightTurn() {
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);
  analogWrite(PWMA, motorTurnSpeed);
  analogWrite(PWMB, motorTurnSpeed);
}

int measureDistance(int triggerPin, int echoPin) {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  return duration * 0.0133 / 2;
}

void loop() {
  int leftDistance = measureDistance(left_Trig, left_Echo);
  int rightDistance = measureDistance(right_Trig, right_Echo);
  if (leftDistance <= MAX_DISTANCE || rightDistance <= MAX_DISTANCE) {
    moveForward();
    delay(100);
  } else {
    if (leftDistance > rightDistance) {
      leftTurn();
      delay(100);
    } else {
      rightTurn();
      delay(100);
    }
  }
  delay(1);
}