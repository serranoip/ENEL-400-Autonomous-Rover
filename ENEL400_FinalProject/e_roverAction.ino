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
        //gyro to keep it go straight
        //having adjustLeft, adjustRight code
        
      }
      else if(dR > 20 && dL > 20) {
        motion.forwardSpeed(75);
        //same gyro code to keep it go straight
      }
      else if(dR < 20)  {
        motion.left();
        //gyro to turn it back on track 
      }
      else if(dL < 20)  {
        motion.right();
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
