#include <dummy.h>
#include <analogWrite.h>
#include <esp_task_wdt.h>

/*Viet Trung Dau
   March 21, 2022
   Code refered from https://www.youtube.com/watch?v=ZBfOH7ryFFc  //gyro navigation
                     https://www.youtube.com/watch?v=D7WmrVNSCqE&feature=youtu.be   //extracting gyro sensor value
*/

//declare library
//declare pin locations
//declare parameter

//Testing on Arduino Uno
//having the PWN pin 10, 11 avaiable

#include <Wire.h>                            // Wire library require for I2C protocol
#include <I2Cdev.h>                          // Include I2C protocol
#include <MPU6050.h>                         // Include Gyrometer


//initialization for the RIGHT sensor
const int trigPinR = 25;
const int echoPinR = 26;


//initialization for the LEFT sensor
const int trigPinL = 4;
const int echoPinL = 5;


//motors RIGHT
const int speedPinR = 6; //ENA
const int dir1R = 7;  //advancing
const int dir2R = 8;  //reversing
int mspeedR;

//motor LEFT
const int speedPinL = 9;
const int dir1L = 12; //advancing
const int dir2L = 13; //reversing
int mspeedL;

//constant timeDelay and trial times
const int timeDelay = 500;
const int trials = 1;
const int fullSpeed = 150;

//define the Gyro code    //accredited from
#define DEGREE_METHOD_USING_MICROS

MPU6050 gyroAccelTemp;                       // Declare a MPU6050 object instance

//Define the properties of the MPU-6050 (IMU)

#define GYRO_Z_OFFSET 16                     // Determined using IMU_Zero under File > Examples > MPU6050

#ifdef DEGREE_METHOD_USING_MICROS
bool isFirstLoopComplete;                  // Declaring the isFirstLoopComplete boolean flag
float previousTime;                        // Declaring the value to hold the time
#endif
