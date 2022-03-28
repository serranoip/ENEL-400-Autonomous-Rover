//conditional moving
class roverAction
{
  public:
    sensor meas;
    motor motion;
    gyroAction gyroControl;
    gyro gyroValue;

    float intAngle;
    float currentAngle;

    //code for moving
    void forward() {
      float dR;
      dR = meas.distR();
      float dL;
      dL = meas.distL();

      if (dR > 50 && dL > 50) {
        int clearSpeed = fullSpeed;

        motion.forwardSpeed(clearSpeed);
        gyroControl.straightAhead(10000);   //duration of operation period in 10s
        delay(300);
        dL = meas.distL();
        dR = meas.distR();
      }

      else if (dR > 20 && dL > 20) {
        int cautionSpeed = fullSpeed / 2;

        motion.forwardSpeed(cautionSpeed);
        gyroControl.straightAhead(3000);   //duration of operation period in 3s
        delay(300);
        dL = meas.distL();
        dR = meas.distR();
      }

      else if (dR < 20 && dL > 20)  {
        intAngle = gyroValue.angleInput();
        gyroControl.turn(10);  //set up a gyro code to make it turn 10 degree to the right
        motion.forwardSpeed(10);  //keep moving
        delay(200);
        currentAngle = gyroValue.angleInput();

        if (currentAngle - intAngle > 5)  {
          gyroControl.turn(intAngle);
        }

        delay(300);
        dL = meas.distL();
        dR = meas.distR();
      }

      else if (dR > 20 && dL < 20)  {
        intAngle = gyroValue.angleInput();

        gyroControl.turn(-10);  //set up a gyro code to make it turn 10 degree to the right
        motion.forwardSpeed(10);  //keep moving
        delay(200);
        currentAngle = gyroValue.angleInput();

        if (currentAngle - intAngle > 5)  {
          gyroControl.turn(intAngle);
        }

        delay(300);
        dL = meas.distL();
        dR = meas.distR();
      }

      else  {
        intAngle = gyroValue.angleInput();
        
        if (dR >= dL) {
          gyroControl.turn(-45);
        }
        else if(dR < dL)  {
          gyroControl.turn(45);
        }
        
        motion.forwardSpeed(10);  //keep moving
        delay(200);
        
        currentAngle = gyroValue.angleInput();

        if (currentAngle - intAngle > 5)  {
          gyroControl.turn(intAngle);
        }
        
        delay(300);
        dL = meas.distL();
        dR = meas.distR();
        
      }


      //        else  {
      //
      //        }

      //      if (dR < 7 && dL < 7) {
      //        motion.fullStop();
      //        //wait 5 second and scan again
      //        //if still less than 7 cm
      //        //turn to the side
      //      }
    }

  private:

};
