import processing.serial.*;

Serial myPort;  // Create object from Serial class

float scaleY = 2.0f;
int valueCount = 100;
int stepSize = 1;
int index = 0;

int[] deltaPosArray = new int[valueCount];

void setup() {
  size(1000, 600);
  printArray(Serial.list());
  String portName = Serial.list()[8];

  myPort = new Serial(this, portName, 2000000);

  stepSize = width / deltaPosArray.length;
}


void draw() {
  if ( myPort.available() > 0) {  // If data is available,
    String s = myPort.readString();         // read it and store it in val
    s = s.trim();
    try {
      int v = Integer.parseInt(s);
      println(v);
      if (index >= deltaPosArray.length-1) {
        shiftArray();
      } else {
        index++;
      }
      deltaPosArray[index] = v;
    }
    catch ( NumberFormatException e) {
      println(e);
    }
  }

  background(222);
  drawDeltaPosArray();
}


void drawDeltaPosArray() {
  push();
  translate(0, height/2);
  stroke(200);
  line(0, 0, width, 0);
  
  stroke(0);
  for (int i = 0; i < deltaPosArray.length-1; i++) {
    line(i*stepSize, deltaPosArray[i]*scaleY, i*stepSize+stepSize, deltaPosArray[i+1]*scaleY);
  }
  pop();
}


void shiftArray() {
  for (int i = 0; i < deltaPosArray.length - 1; i++) {
    deltaPosArray[i] = deltaPosArray[i+1];
  }  
}
