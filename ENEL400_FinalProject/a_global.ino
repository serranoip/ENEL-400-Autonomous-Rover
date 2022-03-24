//declare library
//declare pin locations
//declare parameter

#include <Wire.h>                            // Wire library require for I2C protocol
//#include <I2Cdev.h>                          // Include I2C protocol
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
