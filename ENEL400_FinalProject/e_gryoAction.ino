//making turns by reading gyro values
//going straight straight
class gyroAction
{
  public:
    gyro gyroMotor;
    motor Movement;



    void turn(int desiredAngle) { //90 for turning left //-90 for turning right //from the calibration point //not depending on the rover direction at that moment
      float angleValue = gyroMotor.angleInput();

      while (abs(desiredAngle - angleValue) > 5 ) {

        if (desiredAngle - angleValue > 0)  {
          Movement.left(35);
        }
        if (desiredAngle - angleValue > 0)  {
          Movement.right(35);
        }
        float angleValue = gyroMotor.angleInput();  //update the angle value
      }
      Movement.fullStop();
    }

    void straightAhead(int duration)  {
      float angleValue = gyroMotor.angleInput();
      unsigned long desitination = millis() + duration;

      while (millis() < desitination) {
        float angleActual = gyroMotor.angleInput();

        int rightSpeed = fullSpeed / 2 - (angleActual - angleValue);    //matching the speed of the right wheel to the angle offset
        int leftSpeed = fullSpeed / 2 + (angleActual - angleValue);

        Movement.right(rightSpeed);
        Movement.left(leftSpeed);

      }
      Movement.fullStop();
    }

  private:

};
