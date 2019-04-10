import processing.serial.*;
import ddf.minim.*;

AudioPlayer audioControl;
Serial audioPort;
Minim minim;
  boolean print = true;

void setup(){
  String portName = Serial.list()[3];
  audioPort = new Serial (this, portName, 9600);
  minim = new Minim(this);
  
  audioControl = minim.loadFile("audio/dontpress_button/1.wav");
  
  size(200,200);
}

void draw(){
  if(print){
  printArray(Serial.list());
  print = false;
  }
}

void mouseClicked(){
  
}

void stop(){
  audioControl.close();
  minim.stop();
}
