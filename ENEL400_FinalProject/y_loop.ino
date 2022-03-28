void loop() {
  gyroAction Action;
  sensor disValue;

  int angle;

  //  sensor sonicSensor;
  //  float dL;
  //  dL = sonicSensor.distL();

  gyro gyroMotor;

  float angleValue;
  angleValue = gyroMotor.angleInput();
  Serial.println(angleValue);
  
//  for ( int i = 1; i < 5; i++) {
//    angle = 90 * i;
//    roverAction();
//    delay(1000);
//    Action.turn(angle);
//    delay(100);
//  }
//  
//  Serial.println(disValue.distR());
//  Serial.println(disValue.distL());

}
