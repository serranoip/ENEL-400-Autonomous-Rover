//declare library
//declare pin locations
//declare parameter

#include <Wire.h>                            // Wire library require for I2C protocol
#include <I2Cdev.h>                          // Include I2C protocol
#include <MPU6050.h>                         // Include Gyrometer

//initialization for the RIGHT sensor
const int trigPinR = 2;
const int echoPinR = 4;


//initialization for the LEFT sensor
const int trigPinL = 5;
const int echoPinL = 12;


//motors RIGHT
const int speedPinR = 13; //ENA
const int dir1R = 14;  //advancing
const int dir2R = 15;  //reversing 
int mspeedR;

//motor LEFT
const int speedPinL = 16;
const int dir1L = 17; //advancing
const int dir2L = 18; //reversing
int mspeedL;

//constant timeDelay and trial times
const int timeDelay = 500;
const int trials = 20;
const int fullSpeed = 150;

//define the Gyro code    //accredited from 
#define DEGREE_METHOD_USING_MICROS

MPU6050 gyroAccelTemp;                       // Declare a MPU6050 object instance

//Define the properties of the MPU-6050 (IMU)
float gyroDegreeNew;
float gyroDegreeOld;

#define GYRO_Z_OFFSET 16                     // Determined using IMU_Zero under File > Examples > MPU6050

#ifdef DEGREE_METHOD_USING_MICROS
  bool isFirstLoopComplete;                  // Declaring the isFirstLoopComplete boolean flag
  float previousTime;                        // Declaring the value to hold the time
#endif
