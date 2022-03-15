#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int trigPin = 7;
int echoPin = 6;
float pingTravelTime;
float distance;

int trials = 20;
float averageDist;
float accDist;

int timeDelay = 300;

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Distance: ");

  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  accDist = 0;
  for(int j=0; j < trials; j++)  {
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
  //Serial.println(pingTravelTime);
  lcd.clear();
  lcd.setCursor(0,1);
  distance = 0.0343 * (averageDist / 2) / 2.54; //in inches
  lcd.print(distance);
  delay(timeDelay);
}
