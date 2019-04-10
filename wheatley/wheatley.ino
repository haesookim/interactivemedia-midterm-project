#include <Servo.h>

Servo jumpServo;
int jumpPin = 3;
//bool jumpSig = false;

Servo turnServo;
int turnPin = 5;
//bool turnSig = false;
int originPos = 90;

int buttonPin = 8;
int distVal = analogRead(A0);

int eyePin = 13;
//connect blue LED along with

void setup() {
  Serial.begin(9600);

  jumpServo.attach(jumpPin);
  turnServo.attach(turnPin);

  pinMode(buttonPin, INPUT);
  pinMode(eyePin, OUTPUT); 
}

void loop() {

  //jump when shocked
  if (digitalRead(buttonPin) == HIGH) {
    headUp(60, 200); //adjust to ideal delay timing
  }

  delay(200);
  digitalWrite(eyePin, HIGH);
  delay(1000);
  digitalWrite(eyePin, LOW);
  delay(1000);
  Serial.println("Um");
  
 
}

void headUp(int Angle, int delayTime) {
  jumpServo.write(Angle);
  delay(delayTime);
  jumpServo.write(0);
}

void turnHead(int turnNum, int turnAngle1, int turnAngle2) {
  //int turnAngle = 120;
  int delayTime = 500;
  for (int i = 0; i < turnNum; i++) {
    turnServo.write(turnAngle1);
    delay(delayTime);
    turnServo.write(turnAngle2);
    delay(delayTime);
  }
  turnServo.write(originPos);
}
