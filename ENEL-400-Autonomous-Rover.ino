#include <NewPing.h>

//#include "ultrasonic.h"
#include "motor.h"
#define TRIGGER_PIN_LEFT 12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN_LEFT    39
#define TRIGGER_PIN_RIGHT   4  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN_RIGHT    36  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE     300 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing Rsensor(TRIGGER_PIN_RIGHT, ECHO_PIN_RIGHT, MAX_DISTANCE);
NewPing Lsensor(TRIGGER_PIN_LEFT,  ECHO_PIN_LEFT,  MAX_DISTANCE);

int distR;
int distL;

int valid_distR;
int valid_distL;
void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(115200);
  motorSetup();
}

void loop() {
  delay(50);
  while( !(distR = Rsensor.ping_cm()) ){
    delay(50);
  }
  delay(50);
  while( !(distL = Lsensor.ping_cm()) ){
    delay(50);
  }

  Serial.print("distL: ");
  Serial.print(distL);
  Serial.print(",  distR: ");
  Serial.println(distR); 
  
  if (distR < 45 || distL < 45){
    int diff = (distR>50?50:distR) - (distL>50?50:distL);
    move(70,true,diff*diff*diff/40000);
  }
  else {
    move(75);
  }
}
  
