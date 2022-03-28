void setup()  {
  Serial.begin(9600);

  // RIGHT sensor //
  pinMode(trigPinR, OUTPUT);
  pinMode(echoPinR, INPUT);  

  // LEFT sensor
  pinMode(trigPinL, OUTPUT);
  pinMode(echoPinL, INPUT);

  // Motor on the Right
  pinMode(speedPinR, OUTPUT);
  pinMode(dir1R, INPUT);
  pinMode(dir2R, INPUT);

  // Motor on the Left
  pinMode(speedPinL, OUTPUT);
  pinMode(dir1L, INPUT);
  pinMode(dir2L, INPUT);

  // Gyro
    Serial.begin(9600);                      // Initialize Serial Communication

  // Initialize the IMU
  Wire.begin();
  Serial.println("Initializing I2C devices...");
  gyroAccelTemp.initialize();

  // Verify IMU connection
  Serial.println("Testing device connections...");
  Serial.println(gyroAccelTemp.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

  gyroAccelTemp.CalibrateGyro();                  // Fully calibrate gyro in about 15 loops
  Serial.println("Calibration complete");         // Notify when calibration is complete
  /* The following will NOT get rid of the noise produce by the IMU but they will ensure that
      the average values are at 0 to a certain extent
      (Refer to the IMU Error Determination code and the MPU6050 tutorial video for more details)
  */
  // Set Gyroscope Offsets
  gyroAccelTemp.setZGyroOffset(GYRO_Z_OFFSET);    // Set the Z gyroscope offset

  // IMPORTANT: If you do not calibrate after setting your offset, there will be error
  gyroAccelTemp.CalibrateGyro(6);                 // Fine Tuning purposes of gyroscope
  Serial.println("Fine Tuning Complete");         // Notify when fine tuning is complete


  // Start the rover
  motor motion;
  motion.powerUp();
}
