#include <NewPing.h>

//#include "ultrasonic.h"
#include "motor.h"
#define TRIGGER_PIN_LEFT 12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN_LEFT    39
#define TRIGGER_PIN_RIGHT   4  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN_RIGHT    36  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE     100 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing Rsensor(TRIGGER_PIN_RIGHT, ECHO_PIN_RIGHT, MAX_DISTANCE);
NewPing Lsensor(TRIGGER_PIN_LEFT,  ECHO_PIN_LEFT,  MAX_DISTANCE);

int distR;
int distL;
int lastscan;

int valid_distR;
int valid_distL;
void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(115200);
  motorSetup();

  lastscan = millis();
}

void loop() {
  delay(50);
  lastscan = millis();
  distL = Lsensor.ping_cm(); 
  distL = distL?distL:100;
  
  Serial.print("distL: ");
  Serial.print(distL);
  Serial.print(",  dtime: ");
  Serial.println(millis()-lastscan);
  
  delay(50);
  lastscan = millis();
  distR = Rsensor.ping_cm();
  distR = distR?distR:100;
  
  Serial.print("distR: ");
  Serial.print(distR);
  Serial.print(",  dtime: ");
  Serial.println(millis()-lastscan);

  Serial.println();
  lastscan = millis();

  int speed = distR>distL?distL:distR;
  
  if (distR < 50 || distL < 50){
    int diff = (distR>60?60:distR) - (distL>60?60:distL);
    move(70,true,(float)diff/50);
    Serial.printf("speed: %d, diff: %f, olddiff: %f\n", speed, (float)diff/40, (float)(diff/40));
  }
  else {
    move(speed);
    Serial.printf("speed: %d, diff: %f\n", speed, 0.0);
  }
}
  
