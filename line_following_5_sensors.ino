#include "PID_v1.h"
#include "Motor.h"
//#define DEBUG                      //To print the debugging data over serial monitor(0,1)
#define PRINT_TIME_HW 200
//#define DEBUG_SENSOR 1              //To check sensor reading only, over serial monitor(0,1)
//#define DEBUG_MOTOR
//#define BW                        // To follow black line over white surface
#define WB                      // To follow white line over black surface

#define MAX_POWER 255
#define MIN_POWER 0
double Setpoint, Input, Output;                                                                             //[100   kp=12]   [255 kp=30]  [150 kp=15 ki=0.002]

//Specify the links and initial tuning parameters
double Kp = 30, Ki = 0.002, Kd = 50;   //kp=30
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, REVERSE);

Motor motorLeft(2, 3, 6, Motor::ANALOG);
Motor motorRight(4, 5, 9, Motor::ANALOG);

boolean senD[] = {0, 0, 0, 0, 0}; //Array for holding digital values of sensor

byte ml, mr;
unsigned long currenthw[] = {0, 0, 0, 0};

void setup()
{
  Setpoint = 0;
#ifdef DEBUG
  Serial.begin(9600);
#endif
  Serial.println("NNALUNA!!");
  delay(1000);
  Setpoint = 0;
  myPID.SetMode(AUTOMATIC);
  myPID.SetOutputLimits(-MAX_POWER, MAX_POWER);
  myPID.SetSampleTime(2000);
}

void loop()
{
#ifdef DEBUG_MOTOR
  motorLeft.goForward(255);
  motorRight.goForward(255);
  delay(5000);
  motorLeft.freeze();
  motorRight.goForward(255);
  delay(5000);
  motorLeft.goForward(255);
  motorRight.freeze();
#endif
#ifndef DEBUG_MOTOR
#ifndef DEBUG_SENSOR
  getSensor();
  //Max Error -10...0....10
  //if (senD[0] == 0 && senD[1] == 0 && senD[2] == 0 && senD[3] == 0 && senD[4] == 0 && senD[5] == 0)  stp();
  //else if (senD[0] == 1 && senD[1] == 1 && senD[2] == 1 && senD[3] == 1 && senD[4] == 1 && senD[5] == 1) stp();             //kp=15
  if (senD[0] == 0 && senD[1] == 0 && senD[2] == 0 && senD[3] == 0 && senD[4] == 1) Input = -10;
  else if (senD[0] == 0 && senD[1] == 1 && senD[2] == 1 && senD[3] == 1 && senD[4] == 1)Input = -9;
  else if (senD[0] == 0 && senD[1] == 0 && senD[2] == 1 && senD[3] == 1 && senD[4] == 1)Input = -8;
  else if (senD[0] == 0 && senD[1] == 0 && senD[2] == 0 && senD[3] == 1 && senD[4] == 1)Input = -7;
  else if (senD[0] == 0 && senD[1] == 0 && senD[2] == 1 && senD[3] == 1 && senD[4] == 0)Input = - 3;
  else if (senD[0] == 0 && senD[1] == 1 && senD[2] == 1 && senD[3] == 1 && senD[4] == 0) Input = 0;
  else if (senD[0] == 0 && senD[1] == 1 && senD[2] == 1 && senD[3] == 0 && senD[4] == 0)Input = 3;
  else if (senD[0] == 1 && senD[1] == 1 && senD[2] == 0 && senD[3] == 0 && senD[4] == 0)Input = 7;
  else if (senD[0] == 1 && senD[1] == 1 && senD[2] == 1 && senD[3] == 0 && senD[4] == 0)Input = 8;
  else if (senD[0] == 1 && senD[1] == 1 && senD[2] == 1 && senD[3] == 1 && senD[4] == 0)Input = 9;
  else if (senD[0] == 1 && senD[1] == 0 && senD[2] == 0 && senD[3] == 0 && senD[4] == 0)Input = 10;

  myPID.Compute();
  byte leftMotorPower = 0, rightMotorPower = 0;
  if (Output < 0) //robot should move right value comes negative
  {

    leftMotorPower = MAX_POWER;
    rightMotorPower = MAX_POWER + Output;
  }
  else if (Output > 0)//robot should move left value comes positive
  {
    rightMotorPower = MAX_POWER;
    leftMotorPower = MAX_POWER - Output;
  }
  mr = rightMotorPower; ml = leftMotorPower;
  motorLeft.goForward(leftMotorPower);
  motorRight.goForward(rightMotorPower);
  // Serial.println(Output);
#ifdef DEBUG
  debugSensorAlong();

  debugPID();
  debugMotor();

#endif

#endif

#ifdef DEBUG_SENSOR
  debugSensor();
#endif
#endif
}
