//initialize sensor
//calculate distance

class sonicSensor
{
  public:
    float sensorRight()
    {
      int accDistR = 0;
      float averageDistR;
      float pingTravelTimeR;
      float distanceR;
      
      for(int i=0; i < trials; i++)  {  //return the average value of 20 trials instead of one at a time -- more stable data
        digitalWrite(trigPinR, LOW);
        delayMicroseconds(10);
        digitalWrite(trigPinR, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPinR, LOW);
        pingTravelTimeR = pulseIn(echoPinR, HIGH); 
        delay(25);
        accDistR = accDistR + pingTravelTimeR;  //total value of the accDist in (trails) times
      }
      averageDistR = accDistR / trials;
      //the value of the distance value on the RIGHT sensor
      distanceR = (0.0343 * averageDistR) / 2; //in cm
      return (float) distanceR;
    }

    float sensorLeft()
    {
      float accDistL = 0;
      float pingTravelTimeL;
      float distanceL;
      float averageDistL;
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
      return (float) distanceL;
    }
  
  private:
  
};
