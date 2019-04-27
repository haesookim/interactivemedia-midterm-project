//#include <NewPing.h>
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

//talking settings
unsigned long talkTimer;
const long talkDelay = 3000;

//base state
int wakeDist = 1000;
bool idle = true;
bool sleeping = false;

//ultrasound distance sensor
const int triggerPin = 10;
const int echoPin = 9;
long duration = 0;

//using the NewPing library
//NewPing sonar(10, 9);
unsigned long pingTimer;
long distance = 0;
const int pingSpeed = 100;

void setup() {
  Serial.begin(9600);

  pingTimer = millis() + pingSpeed;

  jumpServo.attach(jumpPin);
  turnServo.attach(turnPin);

  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(eyePin, OUTPUT);

  digitalWrite(eyePin, LOW);

  /*pinMode(triggerPin, OUTPUT);
    pinMode(echoPin, INPUT);*/
  //don't need these two lines if I'm using the library

  jumpServo.write(0);
  turnServo.write(originPos);
}

void loop() {
  unsigned long currentTime = millis();

//  if (currentTime >= pingTimer) {
//    pingTimer += pingSpeed; // Make sensor 1 fire again 100ms later (pingSpeed)
//    distance = sonar.convert_cm(sonar.ping());
//  }

//  if (distance < wakeDist && sleeping) {
//    sleeping = false;
//    idle = true;
//  } else if (distance > wakeDist) {
//    sleeping = true;
//    idle = false;
//    Serial.println("2"); // reset the shock counter
//  }

  if (sleeping) {
    digitalWrite(eyePin, LOW);
  }

  //idle state
  if (idle) {
          Serial.println("1");
    if (currentTime > talkTimer) {
      talkTimer += talkDelay; // tell wheatley to ramble every 3 secs or so
    }
    digitalWrite(eyePin, HIGH);
    if (currentTime - prevBlinkTime >= idleBlinkDelay) {
      prevBlinkTime = currentTime;
      blinkEye(1, 0);
    }

    //    if (currentTime - prevTurnTime >= idleTurnDelay) {
    //      prevTurnTime = currentTime;
    //      turnHead(1, 150, 30);
    //    }
    // adjust shockcount in processing
  }

  //jump when shocked
  if (digitalRead(buttonPin) == LOW) {
    idle = false;
    Serial.println("3"); // tell wheatley to jump
    headUp(30, 200); //adjust to ideal delay timing
    blinkEye(3, 100);
    prevTurnTime = currentTime;
  }

  //old echo related code
  //sleeping state
  //  digitalWrite(triggerPin, LOW);
  //  delayMicroseconds(2);
  //  digitalWrite(triggerPin, HIGH);
  //  delayMicroseconds(10);
  //  digitalWrite(triggerPin, LOW);
  //
  //  duration = pulseIn(echoPin, HIGH);
  //  distance = duration / 29 / 2;
  //  distance = constrain(distance, 0, 2000);
  //
  //  if (distance <= 100 && sleeping) {
  //    idle = true;
  //    sleeping = false;
  //    //Serial.println("1"); //wake up string
  //  } else {
  //    idle = false;
  //    //Serial.println("2"); //going back to sleep string
  //  }

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
