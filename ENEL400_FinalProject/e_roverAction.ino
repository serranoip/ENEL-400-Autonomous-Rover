//conditional moving
class roverAction
{
  public:
    sensor meas;
    motor motion;
    //gyro 

    //code for moving
    void forward() {
      float dR;
      dR = meas.distR();
      float dL;
      dL = meas.distL();

      if(dR > 50 && dL >50) {
        motion.forwardSpeed(150);
      }
      else if(dR > 20 && dL > 20) {
        motion.forwardSpeed(75);
      }
      else if(dR < 20)  {
        motion.left();
      }
      else if(dL < 20)  {
        motion.right();
      }
      else if(dR < 10 && dL < 10) {
        motion.fullStop();
      }
      
    }

  private:
  
};
