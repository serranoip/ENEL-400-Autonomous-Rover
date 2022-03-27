//start and stop

class motor
{
  public:
    void powerUp()
    {
      digitalWrite(dir1R, LOW);  
      digitalWrite(dir2R, LOW);
      digitalWrite(dir1L, LOW);
      digitalWrite(dir2L, LOW);

      digitalWrite(dir1R, HIGH); 
      delay(10);
      digitalWrite(dir1R, LOW);
      delay(10);
      digitalWrite(dir1L, HIGH); 
      delay(10);
      digitalWrite(dir1L, LOW);
      delay(10);
    }
    
    void fullStop() //full stop
    {
      digitalWrite(dir1R, LOW);  
      digitalWrite(dir2R, LOW);
      digitalWrite(dir1L, LOW);
      digitalWrite(dir2L, LOW);
    }
  
    void forwardSpeed(int velocity) //forward at input speed value //minimum velocity 0 and maximum at 255
    {
      digitalWrite(dir1R, HIGH);  
      digitalWrite(dir2R, LOW);
      digitalWrite(dir1L, HIGH);
      digitalWrite(dir2L, LOW);
      analogWrite(speedPinR, velocity);
      analogWrite(speedPinL, velocity);
    }
  
    void backwardSpeed(int velocity)  //go backward
    {
      digitalWrite(dir1R, LOW);  
      digitalWrite(dir2R, HIGH);
      digitalWrite(dir1L, LOW);
      digitalWrite(dir2L, HIGH);
      analogWrite(speedPinR, velocity);
      analogWrite(speedPinL, velocity);
    }
  
    void right(int turnSpeed) //Turns car to the right  //depending on the setup turning speed
    {
      digitalWrite(dir1R, HIGH);  
      digitalWrite(dir2R, LOW);
      digitalWrite(dir1L, LOW);
      digitalWrite(dir2L, HIGH);
      analogWrite(speedPinR, turnSpeed);
      analogWrite(speedPinL, turnSpeed);  //does this make the rover turn smoother?
    }
  
    void left(int turnSpeed) //Turns car to the left
    {
      digitalWrite(dir1R, LOW);  
      digitalWrite(dir2R, HIGH);
      digitalWrite(dir1L, HIGH);
      digitalWrite(dir2L, LOW);
      analogWrite(speedPinR, turnSpeed);
      analogWrite(speedPinL, turnSpeed);
    }
  
    void adjustRight() // turn the car slightly to the right
      {
        digitalWrite(dir1L, LOW);
        delay(1);
        digitalWrite(dir1L, HIGH);
      }
      
    void adjustLeft() // turn the car slightly to the right
      {
        digitalWrite(dir1R, LOW);
        delay(1);
        digitalWrite(dir1R, HIGH);
      }
 
  
  private:
    
};
