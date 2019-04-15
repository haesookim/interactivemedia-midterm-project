#include <Servo.h>

//jump servo settings
Servo jumpServo;
const int jumpPin = 3;
//bool jumpSig = false;

//turn servo settings
Servo turnServo;
const int turnPin = 5;
//bool turnSig = false;
int originPos = 90;
unsigned long prevTurnTime = 0;
const long idleTurnDelay = 11000;

//button settings
int buttonPin = 8;
int distVal = analogRead(A0);

//eye (blue LED) settings
int eyePin = 13;
unsigned long prevBlinkTime = 0;
const long idleBlinkDelay = 5000;

//base state
bool idle = false;
bool sleeping = true;

//ultrasound distance sensor
const int triggerPin = 10;
const int echoPin = 9;
long duration = 0;
long distance = 0;

void setup() {
  Serial.begin(9600);

  jumpServo.attach(jumpPin);
  turnServo.attach(turnPin);

  pinMode(buttonPin, INPUT);
  pinMode(eyePin, OUTPUT);

  digitalWrite(eyePin, LOW);

  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);

  jumpServo.write(0);
  turnServo.write(originPos);
}

void loop() {
  unsigned long currentTime = millis();

  //sleeping state
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration / 29 / 2;
  distance = constrain(distance, 0, 2000);
  
  if (distance <= 100 && sleeping) {
    idle = true;
    sleeping = false;
    Serial.println("1"); //wake up string
  } else {
    idle = false;
    Serial.println("2"); //going back to sleep string
  }


  if (sleeping){
        digitalWrite(eyePin, LOW);
    }

  //idle state
  if (idle) {
    digitalWrite(eyePin, HIGH);
    if (currentTime - prevBlinkTime >= idleBlinkDelay) {
      prevBlinkTime = currentTime;
      blinkEye(1, 0);
    }

    if (currentTime - prevTurnTime >= idleTurnDelay) {
      prevTurnTime = currentTime;
      turnHead(1, 150, 30);
    }
// adjust shockcount in processing
  }

  //jump when shocked
  if (digitalRead(buttonPin) == HIGH) {
    idle = false;
    Serial.println("3");
    headUp(30, 200); //adjust to ideal delay timing
    blinkEye(3, 100);
    prevTurnTime = currentTime;
    delay(1000);
  }

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

void blinkEye(int blinkNum, int blinkDelay) {
  for (int i = 0; i < blinkNum; i++) {
    digitalWrite(eyePin, LOW);
    delay(100);
    digitalWrite(eyePin, HIGH);
    delay(blinkDelay);
  }
}
