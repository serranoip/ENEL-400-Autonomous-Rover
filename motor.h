#include <analogWrite.h>

#define FREQ 50

const int ENA = 13;
const int IN1 = 14;
const int IN2 = 0;
const int IN3 = 26;
const int IN4 = 25;
const int ENB = 2;
void motorSetup(){
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}
void mbrake(){
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}
void mstart(){
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
byte move(byte speed = 220, bool forward = true, float direction = 0){
  if (abs(direction) > 1) {
    direction = (direction > 0) - (0 > direction);
  }

  int outsideMotor = direction > 0 ? ENB : ENA;
  int insideMotor = (ENA + ENB) - outsideMotor;

  forward? mforward():mbackward();
  analogWrite(outsideMotor, speed, FREQ);
  analogWrite(insideMotor, int(speed*(1-abs(direction))), FREQ);
  return 0;
}

void dMove(byte speed = 220, bool forward = true, int time_ms = 150, float direction = 0){
  if(move(speed, forward, direction)) return;
  delay(time_ms);
  mbrake();
}

void dTurn(bool right, int time_ms= 100, byte speed = 220){
  right? mright():mleft();
  analogWrite(ENA, speed, FREQ);
  analogWrite(ENB, speed, FREQ);
  delay(time_ms);
  mbrake();
}
