////initialize sensor
////calculate distance


class sensor
{
  public:
    float distR()
    {
      float accDistR = 0;
      float DistanceR;
      float pingTravelTimeR;

      for (int i = 0; i < trials; i++)  { //return the average value of 20 trials instead of one at a time -- more stable data
        digitalWrite(trigPinR, LOW);
        delayMicroseconds(10);
        digitalWrite(trigPinR, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPinR, LOW);
        pingTravelTimeR = pulseIn(echoPinR, HIGH);
        delay(25);
        accDistR = accDistR + pingTravelTimeR;  //total value of the accDist in (trails) times
      }

      DistanceR = (0.0343 / 2) * (accDistR / trials);
      //if (DistanceR < 300)  {
        return (float)DistanceR;
      //}
    }

    float distL()
    {
      float accDistL = 0;
      float DistanceL;
      float pingTravelTimeL;

      for (int i = 0; i < trials; i++)  { //return the average value of 20 trials instead of one at a time -- more stable data
        digitalWrite(trigPinL, LOW);
        delayMicroseconds(10);
        digitalWrite(trigPinL, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPinL, LOW);
        pingTravelTimeL = pulseIn(echoPinL, HIGH);
        delay(25);
        accDistL = accDistL + pingTravelTimeL;  //total value of the accDist in (trails) times
      }

      DistanceL = (0.0343 / 2) * (accDistL / trials);
      return (float)DistanceL;
    }

  private:
};
