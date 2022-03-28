//set up gyro
class gyro 
{
  public:
    float angleInput()
    {
        float gyroZ = gyroAccelTemp.getRotationZ() / 131.0;         // Get current Z axis orientation in degress per second

        if (isFirstLoopComplete) {
            float timeForOneLoop = micros() - previousTime;
            //Serial.println(timeForOneLoop);
            gyroDegreeNew += gyroZ * timeForOneLoop / 1000000.0;
           }
           // NOTE: Try and keep the following code close to the above if statement
           previousTime = micros();
    
           float err = gyroDegreeNew - gyroDegreeOld;
           if(err > 0.3 || err <-0.3)  {
            gyroDegreeOld = gyroDegreeNew;
           }
           
    
         // Change the boolean flag to true to enable collection of gyroscope data
         if (!isFirstLoopComplete) {
          isFirstLoopComplete = true;
         }

         return (float)gyroDegreeOld;
    
    }
   
  private:
    
};
