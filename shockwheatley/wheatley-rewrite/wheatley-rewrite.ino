#include <Servo.h>

Servo jumpServ;
Servo turnServ;
const int jumpPin = 3;
const int turnPin = 5;
int turnPos = 90;

int buttonPin = 8;
int eyePin = 13;

unsigned long currentTime;

const long blinkTime = 5000;
unsigned long blinkTimer;

bool blinking;
unsigned long blinkingTimer;

bool jumping;
unsigned long jumpingTimer;

bool idle;
bool buttonPressed;

void setup() {
  Serial.begin(9600);

  jumpServ.attach(jumpPin);
  turnServ.attach(turnPin);

  pinMode(buttonPin, INPUT);
  pinMode(eyePin, OUTPUT);

  jumpServ.write(0);
  turnServ.write(turnPos);
}

void loop() {
  currenTime = millis();

  if (digitalRead(buttonPin) == LOW && buttonPressed) {
    buttonPressed = true;
  } else if (digitalRead(buttonPin) == HIGH && !buttonPressed) {
    buttonPressed = false;
  }

  if (idle) {
    if (buttonPressed) {
      Serial.println("3");
      blinkEye(3, 100);
      jump(30, 200);
    } else {
      if (currentTime >= blinkTimer) {
        blinkTimer = currentTime + blinkTime;
        blinkEye(1, 0);
        Serial.println("1");
      }
    }
  }

}

void jump(int Angle, int jumpDelay) {
  int jump = 0;
  jumping = false;
  while (jump < 2) {
    if (currentTime >= jumpingTimer){
       jumpingTimer = currentTime + jumpDelay;
       jumping = !jumping;
       jump++;
    }
    if (jumping){
      jumpServo.write(0);
    } else{
      jumpServo.write(Angle);
    }

}

void blinkEye(int times, int blinkDelay) {
  int blinknum = 0;
  blinking = false;
  while (blinknum < 2*times) {
    if (currentTime >= blinkingTimer){
       blinkingTimer = currentTime + blinkDelay;
       blinking = !blinking;
       blinknum++;
    }
    if (blinking){
      digitalWrite(eyePin, HIGH);  
    } else{
      digitalWrite(eyePin, LOW);
    }
  }
}
