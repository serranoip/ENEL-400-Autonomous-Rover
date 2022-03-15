#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int trigPin = 7;
int echoPin = 6;
float pingTravelTime;
float distance;
float distance2;

int trials = 20;
float averageDist;
float accDist;
float compare;

int timeDelay = 100;

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Distance: ");

  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  //initialize the first distance2 value to compare with distance 1 latter in the code 
  digitalWrite(trigPin, LOW);
  delayMicroseconds(10);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  pingTravelTime = pulseIn(echoPin, HIGH); 
  lcd.setCursor(0,1);
  distance2 = 0.0343 * (averageDist / 2) / 2.54;
  delay(25);
  lcd.print(distance2);
}

void loop() {
  // put your main code here, to run repeatedly:
  accDist = 0;
  lcd.clear();
  for(int j=0; j < trials; j++)  {  //return the average value of 20 trials instead of one at a time -- more stable data
    digitalWrite(trigPin, LOW);
    delayMicroseconds(10);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    pingTravelTime = pulseIn(echoPin, HIGH); 
    delay(25);
    accDist = accDist + pingTravelTime;
  }
  averageDist = accDist / trials;
  distance = 0.0343 * (averageDist / 2) / 2.54; //in inches
  
  if(distance < 350/2.54 && distance > 5/2.54) {
    compare = distance - distance2;   //compare the new distance value to the previous one
                                      //if Arduino dectects any spike in the distance -> false value -> keep the previous data
    if( compare < 30 && compare > -30) {
      distance2 = distance;
//      Serial.println("Value of the in-range distance for comparasion:");
//      Serial.println(distance2);
//      Serial.println(distance);
    }
    else  {
    }
    lcd.setCursor(0,1);
    lcd.print(distance2);
    delay(timeDelay);
  }
  else  {
    lcd.setCursor(0,1);
    lcd.print("Out of range");
    lcd.setCursor(0,0);
    lcd.print("Last value:");
    lcd.println(distance2);
//    Serial.println("Value out-of-range:");
//    Serial.println(distance2);
//    Serial.println(distance);
    delay(timeDelay);
  }
}
