// copyright 2017 by Walter Anderson
#ifndef _Robot_h_
#define _Robot_h_

#include <Arduino.h>
#include "AFMotor.h"
#include "Bumper.h"

#define LEFT 0
#define RIGHT 1
#define BACK_RIGHT 0
#define FRONT_RIGHT 1
#define FRONT_LEFT 2
#define BACK_LEFT 3

class Robot
{
 public:
  Robot(void);
  void move(int left, int right);                       // Main method to move robot, takes percentages (-100.0, 100.0) for each 'side' of the robot.
  void stop(void);                                      // Emergency stop of the robot's motors
  int bumpers(void);                                    // Returns the status of the front and rear bumper sensors
 
 private:
  uint8_t MotorStatus[2];                               // array to contain the value of the motor status (assume forward and rear are always set the same).  The motor shield values for this contained in AFMotor.h
  int current_speeds[2];                                // array to contain the current speeds the motors are running at.  (assume forward and rear are always set the same)
  Bumper bumper = Bumper(22,23,24,25);
  AF_DCMotor BckRgt = AF_DCMotor(1);
  AF_DCMotor FrtRgt = AF_DCMotor(2);
  AF_DCMotor FrtLft = AF_DCMotor(3);
  AF_DCMotor BckLft= AF_DCMotor(4);
};

#endif
