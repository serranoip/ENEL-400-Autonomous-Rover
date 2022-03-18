#include "ultrasonic.h"
#include "motor.h"


void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(115200);
  ultrasonicSetup();
  motorSetup();
}

void loop() {

  delay(10);
  sendPing(Rsensor);
  delay(10);
  sendPing(Lsensor);

  //moving straight forward at full speed when the front is clear of obstacles
  if( Lsensor.distCM >= 100 && Rsensor.distCM >= 100)  {
    move(220);
  }
  //moving straight foward at half speed when there are obstacles nearby
  else if( Lsensor.distCM >= 30 && Rsensor.distCM >= 30)  {
    move(110);
  }
  else  {   //stop when an obstacle is closed
    mbrake;
  }
}
  
