
//initialization for the RIGHT sensor
int trigPinR = 7;
int echoPinR = 6;
float pingTravelTimeR;
float distanceR;
float accDistR;
float averageDistR;

//initialization for the LEFT sensor
int trigPinL = 4;
int echoPinL = 5;
float pingTravelTimeL;
float distanceL;
float accDistL;
float averageDistL;

//motors RIGHT
int speedPinR = 3;
int dir1R = 2;  //advancing
int dir2R = 8;  //reversing 
int mspeedR;

//motor LEFT
int speedPinL = 9;
int dir1L = 12; //advancing
int dir2L = 13; //reversing
int mspeedL;

//constant timeDelay and trial times
const int timeDelay = 500;
const int trials = 20;

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600);
  
  // RIGHT sensor //
  pinMode(trigPinR, OUTPUT);
  pinMode(echoPinR, INPUT);  

  // LEFT sensor
  pinMode(trigPinL, OUTPUT);
  pinMode(echoPinL, INPUT);

  // Motor on the Right
  pinMode(speedPinR, OUTPUT);
  pinMode(dir1R, INPUT);
  pinMode(dir2R, INPUT);

  // Motor on the Left
  pinMode(speedPinL, OUTPUT);
  pinMode(dir1L, INPUT);
  pinMode(dir2L, INPUT);
}

void loop() {
  
//the right sensor   
  accDistR = 0;
  for(int i=0; i < trials; i++)  {  //return the average value of 20 trials instead of one at a time -- more stable data
    digitalWrite(trigPinR, LOW);
    delayMicroseconds(10);
    digitalWrite(trigPinR, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPinR, LOW);
    pingTravelTimeR = pulseIn(echoPinR, HIGH); 
    delay(25);
    accDistR = accDistR + pingTravelTimeR;
  }
  averageDistR = accDistR / trials;
  //the value of the distance value on the RIGHT sensor
  distanceR = (0.0343 * averageDistR) / 2; //in cm

// the LEFT sensor
  for(int j=0; j < trials; j++)  {  //return the average value of 20 trials instead of one at a time -- more stable data
    digitalWrite(trigPinL, LOW);
    delayMicroseconds(10);
    digitalWrite(trigPinL, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPinL, LOW);
    pingTravelTimeL = pulseIn(echoPinL, HIGH); 
    delay(25);
    accDistL = accDistL + pingTravelTimeL;
  }
  averageDistL = accDistL / trials;
  //the value of the distance value on the LEFT sensor
  distanceL = (0.0343 * averageDistL) / 2; //in cm

// the motor
  //moving straight forward at full speed when the front is clear of obstacles
  if( distanceL >= 100 && distanceR >= 100)  {
    digitalWrite(dir1R, HIGH);  
    digitalWrite(dir2R, LOW);
    digitalWrite(dir1L, HIGH);
    digitalWrite(dir2L, LOW);
    analogWrite(speedPinR, 255);
    analogWrite(speedPinL, 255);
   }
   
  //moving straight foward at half speed when there are obstacles nearby
  else if( distanceL >= 30 && distanceR >= 30)  {
    digitalWrite(dir1R, HIGH);  
    digitalWrite(dir2R, LOW);
    digitalWrite(dir1L, HIGH);
    digitalWrite(dir2L, LOW);
    analogWrite(speedPinR, 255);
    analogWrite(speedPinL, 255);
   }

  else  {   //stop when an obstacle is closed
    digitalWrite(dir1R, LOW);  
    digitalWrite(dir2R, LOW);
    digitalWrite(dir1L, LOW);
    digitalWrite(dir2L, LOW);
  }
}
  
