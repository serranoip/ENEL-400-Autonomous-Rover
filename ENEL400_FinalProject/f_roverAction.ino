//conditional moving
class roverAction
{
  public:
    sensor meas;
    motor motion;
    gyroAction gyroControl;

    //code for moving
    void forward() {
      float dR;
      dR = meas.distR();
      float dL;
      dL = meas.distL();

      if(dR > 50 && dL >50) {
        int clearSpeed = fullSpeed;
        motion.forwardSpeed(clearSpeed);
        gyroControl.straightAhead(10000);   //duration of operation period in 10s
        
      }
      else if(dR > 20 && dL > 20) {
        int cautionSpeed = fullSpeed/2;
        motion.forwardSpeed(cautionSpeed);
        gyroControl.straightAhead(3000);   //duration of operation period in 3s
      }
      else if(dR < 20)  {
        gyroControl.turn(90);  //set up a gyro code to make it turn 90 degree
        motion.forwardSpeed(50);  //keep moving
        //gyro to turn it back on track 
      }
      else if(dL < 20)  {
        gyroControl.turn(-90);
        motion.forwardSpeed(50);
        //gyro to turn it back on track
      }
      else if(dR < 7 && dL < 7) {
        motion.fullStop();
        //wait 5 second and scan again 
        //if still less than 7 cm 
        //turn to the side
      }
    }

  private:
  
};
