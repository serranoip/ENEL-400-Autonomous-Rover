#include <analogWrite.h>

const int ENA = 19;
const int IN1 = 22;
const int IN2 = 21;
const int IN3 = 2;
const int IN4 = 13;
const int ENB = 14;
void msetup(){
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}
void brake(){
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}
void start(){
  analogWrite(ENA, 220);
  analogWrite(ENB, 220);
}
void mbackward(){
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void mforward(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void mright(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void mleft(){
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}


/*------------------------------------------------------------------------------------------*/


void dMove(bool forward = true, int time_ms = 150, float direction = 0, byte speed = 220){
  if (abs(direction) > 1) {
    //direction must be between -1 & 1
    return;
  }

  int outsideMotor = direction > 0 ? ENB : ENA;
  int insideMotor = (ENA + ENB) - outsideMotor;
  
  forward? mforward():mbackward();
  analogWrite(outsideMotor, speed);
  analogWrite(insideMotor, int(speed*(1-abs(direction))));
  delay(time_ms);
  brake();
}
void dTurn(bool right, int time_ms= 100, byte speed = 220){
  right? mright():mleft();
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
  delay(time_ms);
  brake();
}
