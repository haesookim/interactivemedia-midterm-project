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
  jumpServo.write(Angle);
  delay(jumpDelay);
  jumpServo.write(0);
}

void blinkEye(int times, int blinkDelay) {
  for (int i = 0; i < blinkNum; i++) {
    digitalWrite(eyePin, LOW);
    delay(100);
    digitalWrite(eyePin, HIGH);
    delay(blinkDelay);
  }
}
