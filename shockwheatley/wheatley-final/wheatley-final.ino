//#include <NewPing.h>
#include <Servo.h>

//jump servo settings
Servo jumpServo;
const int jumpPin = 3;

//button settings
int buttonPin = 8;
int distVal = analogRead(A0);

//eye (blue LED) settings
int eyePin = 13;
unsigned long prevBlinkTime = 0;
const long idleBlinkDelay = 5000;

//talking settings
unsigned long talkTimer;
const long talkDelay = 7000;

//base state
bool idle = true;
bool sleeping = false;

void setup() {
  Serial.begin(9600);

  pingTimer = millis() + pingSpeed;

  jumpServo.attach(jumpPin);
  turnServo.attach(turnPin);

  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(eyePin, OUTPUT);

  digitalWrite(eyePin, LOW);

  jumpServo.write(0);
}

void loop() {
  unsigned long currentTime = millis();

  if (sleeping) {
    digitalWrite(eyePin, LOW);
  }

  //idle state
  if (idle) {
    if (currentTime > talkTimer) {
      talkTimer += talkDelay; 
      // tell wheatley to ramble every 3 secs or so
      Serial.write("1\n"); // This is the 'talk' signal
      headUp(10, 500);
    }
    digitalWrite(eyePin, HIGH);
    if (currentTime - prevBlinkTime >= idleBlinkDelay) {
      prevBlinkTime = currentTime;
      blinkEye(1, 0);
    }
  }

  //jump when shocked
  if (digitalRead(buttonPin) == LOW) {
    idle = false;
    Serial.write("3\n"); // tell wheatley to jump
    headUp(50, 100); //adjust to ideal delay timing
    blinkEye(3, 100);
    idle = true;
  }
}

void headUp(int Angle, int delayTime) {
  jumpServo.write(Angle);
  delay(delayTime);
  jumpServo.write(0);
}

void blinkEye(int blinkNum, int blinkDelay) {
  for (int i = 0; i < blinkNum; i++) {
    digitalWrite(eyePin, LOW);
    delay(100);
    digitalWrite(eyePin, HIGH);
    delay(blinkDelay);
  }
}
