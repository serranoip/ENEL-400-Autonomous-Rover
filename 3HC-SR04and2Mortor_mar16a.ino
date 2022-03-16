//the idea here is to have at least 2 ultrasonic sensor in the front at 2 different angle
//to control to turn left or right of the rover
//when one sensor measures distance at below 30cm
//the rover turns the other way
//if both sensors detect the distance at lower than 30cm
//stops
//if the third sensor at the back is clear
//the rover reverses backward
 

//initialization for the RIGHT sensor
int trigPinR = 7;
int echoPinR = 6;
float pingTravelTimeR;
float distanceR;
float distance2R;

float averageDistR;
float accDistR;
float compareR;

//initialization for the LEFT sensor
int trigPinL = 4;
int echoPinL = 5;
float pingTravelTimeL;
float distanceL;
float distance2L;

float averageDistL;
float accDistL;
float compareL;

//initialization for the BACK sensor


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
int timeDelay = 150;
int trials = 20;

void setup() {
  // RIGHT sensor
  pinMode(trigPinR, OUTPUT);
  pinMode(echoPinR, INPUT);
  Serial.begin(9600);
  
  digitalWrite(trigPinR, LOW);
  delayMicroseconds(10);
  digitalWrite(trigPinR, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinR, LOW);
  pingTravelTimeR = pulseIn(echoPinR, HIGH); 

  distance2R = 0.0343 * (averageDistR / 2);

  // LEFT sensor
  pinMode(trigPinL, OUTPUT);
  pinMode(echoPinL, INPUT);

  digitalWrite(trigPinL, LOW);
  delayMicroseconds(10);
  digitalWrite(trigPinL, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinL, LOW);
  pingTravelTimeL = pulseIn(echoPinL, HIGH); 

  distance2L = 0.0343 * (averageDistL / 2);


// BACK sensor

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
// the RIGHT sensor
  accDistR = 0;
  
  for(int j=0; j < trials; j++)  {  //return the average value of 20 trials instead of one at a time -- more stable data
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
  distanceR = (0.0343 * averageDistR) / 2; //in cm
  
  if(distanceR < 350 && distanceR > 5) {
    compareR = distanceR - distance2R;   //compare the new distance value to the previous one
                                      //if Arduino dectects any spike in the distance -> false value -> keep the previous data
    if( compareR < 30 && compareR > -30) {
      distance2R = distanceR;
    }
    else  {
    }
    Serial.print("Distance RIGHT: ");
    Serial.println(distance2R);
  }
  else  {
    Serial.println("Out of range");
  }

// the LEFT sensor
  accDistL = 0;
  
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
  distanceL = (0.0343 * averageDistL) / 2; //in cm
  
  if(distanceL < 350 && distanceL > 5) {
    compareL = distanceL - distance2L;   //compare the new distance value to the previous one
                                      //if Arduino dectects any spike in the distance -> false value -> keep the previous data
    if( compareL < 30 && compareL > -30) {
      distance2L = distanceL;
    }
    else  {
    }
    Serial.print("Distance LEFT: ");
    Serial.println(distance2L);
  }
  else  {
    Serial.println("Out of range");
  }

//the motor

// Motor for avoiding obstacle
  //moving foward at full speed when it is clear of obstacles
   if( distance2L >= 50 && distance2R >= 50)  {
    digitalWrite(dir1R, HIGH);  
    digitalWrite(dir2R, LOW);
    digitalWrite(dir1L, HIGH);
    digitalWrite(dir2L, LOW);
    analogWrite(speedPinR, 255);
    analogWrite(speedPinL, 255);
   }

  //moving fwd at half speed when it detect a potential obstacles in front
  else if ( distance2L >= 20 && distance2R >= 20) {
    digitalWrite(dir1R, HIGH);  
    digitalWrite(dir2R, LOW);
    digitalWrite(dir1L, HIGH);
    digitalWrite(dir2L, LOW);
    analogWrite(speedPinR, 150);
    analogWrite(speedPinL, 150);
  }
  //turning right and then moving straight
  else if ( distance2L < 20 && distance2L > 20) {
    for ( distance2L < 20)  {
      
    }
    for ( distance2L > 20)  {
      
    }
  }
        //how to make it going straight again as the intial path when it is turned side way?????

        
  //turning right and then moving straight

  //moving backward
