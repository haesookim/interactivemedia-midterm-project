import processing.serial.*;
import ddf.minim.*;

AudioPlayer pain1;
AudioPlayer pain2;
AudioPlayer pain3;
AudioPlayer pain4;
AudioPlayer pain5;

AudioPlayer press1;
AudioPlayer press2;
AudioPlayer press3;
AudioPlayer press4;
AudioPlayer press5;

AudioPlayer dontpress1;
AudioPlayer dontpress2;
AudioPlayer dontpress3;
AudioPlayer dontpress4;
AudioPlayer dontpress5;

Serial audioPort;
Minim minim;
boolean print = true;
String printresult;
String response;
AudioPlayer[][] playerArray = {{pain1, pain2, pain3, pain4, pain5}, {press1, press2, press3, press4, press5}, {dontpress1, dontpress2, dontpress3, dontpress4, dontpress5}};

int shockCount;

long prevTime = 0;
long rewindTimer = 0;
long rewindDelay = 5000;
long currentTime = millis();

boolean finished = true;

void setup() {
  String portName = Serial.list()[3];
  audioPort = new Serial (this, "/dev/cu.usbmodem14201", 9600);
  minim = new Minim(this);

  audioPort.bufferUntil(10);

  String[] loadArray = {"pain", "press", "dontpress"};
  for (int i = 0; i< 3; i++) {
    for (int j = 0; j<5; j++) {
      playerArray[i][j] = minim.loadFile("audio/"+loadArray[i]+"/"+(j+1)+".wav");
    }
  }

  size(200, 200);
}

void draw() {
  currentTime = millis();
  if (audioPort.available() > 0 && finished) {
    finished = false;
    printresult = audioPort.readStringUntil('\n');
    if (printresult != null) {
      String serialVal = printresult.trim();
      println(serialVal);

      if (serialVal.equals("2")) {
        shockCount = 0;
      }

      if (serialVal.equals("3")) { // if signal is 'pain'
        scream();
      }
      
      if (serialVal.equals("1")) { // if signal is 'talk'
        if (shockCount > 0) {
          int idleplayer = (int)random(0, 4);         
          playerArray[1][idleplayer].play();
          while (true) {
            String tempVal;
            if (audioPort.available() > 0) {
              printresult = audioPort.readStringUntil('\n');
              if (printresult != null) {
                tempVal = printresult.trim();
                if (tempVal.equals("3")) {
                  playerArray[1][idleplayer].mute();
                  playerArray[1][idleplayer].rewind();
                  scream();
                  rewindTimer = millis() + rewindDelay;
                  break;
                }
              }
            }
            if (millis() > rewindTimer) {
              rewindTimer = millis() + rewindDelay;
              break;
            }
          }
          playerArray[1][idleplayer].unmute();
          playerArray[1][idleplayer].rewind();
        } else if (shockCount == 0) {
          int idleplayer = (int)random(0, 4);         
          playerArray[2][idleplayer].play();
          while (true) {
            String tempVal;
            if (audioPort.available() > 0) {
              printresult = audioPort.readStringUntil('\n');
              if (printresult != null) {
                tempVal = printresult.trim();
                if (tempVal.equals("3")) {
                  playerArray[2][idleplayer].mute();
                  playerArray[2][idleplayer].rewind();
                  scream();
                  rewindTimer = millis() + rewindDelay;
                  break;
                }
              }
            }
            if (millis() > rewindTimer) {
              rewindTimer = millis() + rewindDelay;
              break;
            }
          }
          playerArray[2][idleplayer].unmute();
          playerArray[2][idleplayer].rewind();
        }
      }
      
      finished = true;
    }
  }
}


void scream() {
  int player = (int)random(0, 4);
  playerArray[0][player].play();
  delay(1000);
  playerArray[0][player].rewind();
  shockCount += 1;
}


void dontpressbutton() {
}

void waitbreak(int time, String shock) {
  while (currentTime - prevTime < time) {
    prevTime = currentTime;
    if (shock.equals("3")) {
      break;
    }
    println("caught?");
  }
}

void stop() {
  for (int i = 0; i< 3; i++) {
    for (int j = 0; j<5; j++) {
      playerArray[i][j].close();
    }
  }
  minim.stop();
  super.stop();
}
