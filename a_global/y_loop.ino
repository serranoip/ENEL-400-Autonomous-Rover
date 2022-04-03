void loop() {
  //  gyroAction Action;
  esp_task_wdt_init(30, false);


  //  sensor sonicSensor;
  //  float dL;
  //  dL = sonicSensor.distL();

  gyro gyroMotor;
  float angleValue;
  angleValue = gyroMotor.angleInput();
  Serial.println("Angle value: ");
  Serial.println(angleValue);

  sensor sensorValue;
  int rightV = sensorValue.distR();
  Serial.println("Distance Rvalue: ");
  Serial.println(rightV);
  
  int leftV = sensorValue.distL();
  Serial.println("Distance Lvalue: ");
  Serial.println(leftV);

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
  delay(100);
}
