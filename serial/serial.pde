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
AudioPlayer[][] playerArray = {{pain1, pain2, pain3, pain4, pain5}, {press1, press2,press3, press4, press5}, {dontpress1, dontpress2,dontpress3, dontpress4, dontpress5}};

void setup() {
  String portName = Serial.list()[3];
  audioPort = new Serial (this, portName, 9600);
  minim = new Minim(this);

  audioPort.bufferUntil(10);
  
  String[] loadArray = {"pain", "press", "dontpress"};
  for (int i = 0; i< 3; i++){
    for (int j = 1; j<6; j++){
      playerArray[i][j] = minim.loadFile("audio/"+loadArray[i]+"/"+j+".wav");
    }
  }

  size(200, 200);
}

void draw() {
  if (audioPort.available() > 0) {
    printresult = audioPort.readStringUntil('\n');
    if (printresult != null){
      println(printresult.trim());
      if (printresult.trim().equals("3")) {
        int player = (int)random(1,6);
        println("play");
        playerArray[0][player].play();
        delay(1000);
        audioControl.rewind();
      }
    }
  }
}

void mouseClicked() {
  println("play");
  audioControl.play();
}

void stop() {
  audioControl.close();
  minim.stop();
  super.stop();
}
