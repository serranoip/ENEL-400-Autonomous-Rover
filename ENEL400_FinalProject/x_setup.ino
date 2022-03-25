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

  // Start the rover
  motor motion;
  motion.powerUp();
}
