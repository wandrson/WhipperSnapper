// copyright 2017 by Walter Anderson
#include "Robot.h"

// Constructor
Robot::Robot()
{
  current_speeds[LEFT] = 0;
  current_speeds[RIGHT] = 0;
  MotorStatus[LEFT] = BRAKE;
  MotorStatus[RIGHT] = BRAKE;
}

int Robot::bumpers(void)
{
  return(bumper.status());
}

// This method is intended to be used when a sensor indicates a need for an immediate
// stop of the robots motion
void Robot::stop(void)
{
  // First stop the motors from actually running
  BckLft.run(RELEASE);
  BckRgt.run(RELEASE);
  FrtLft.run(RELEASE);
  FrtRgt.run(RELEASE);

  // Now update the various status variables
  MotorStatus[LEFT] = RELEASE;
  MotorStatus[RIGHT] = RELEASE;
  current_speeds[LEFT] = 0;
  current_speeds[RIGHT] = 0;
}

// Basic method for controlling the motion of the robot.  The
// variable left and right contain signed percentages. A negative
// percentage turns the respective motive in reverse at the percentage
// of full speed.
void Robot::move(int left, int right)
{
  uint8_t lms, rms, ltmp, rtmp, indx;
  int linc, rinc;                               // Incremental change values for speed change
  int num_units=10;                             // Number of steps to use when ramping speed
    
  // First determine new motor status from the absolute value of the provided speeds
  if (left < 0) 
    lms = BACKWARD;
  else if (left > 0) 
    lms = FORWARD;
  else
    lms = RELEASE;
  if (right < 0) 
    rms = BACKWARD;
  else if (right > 0) 
    rms = FORWARD;
  else 
    rms = RELEASE;

  // Save these new values
  MotorStatus[LEFT] = lms;
  MotorStatus[RIGHT] = rms;
  //Serial.print("Left status: ");
  //Serial.println(lms);
  //Serial.print("Right status: ");
  //Serial.println(rms);
  
  // Now change the motor status to the new calculated value
  BckLft.run(lms);
  BckRgt.run(rms);
  FrtLft.run(lms);
  FrtRgt.run(rms);

  // Ramp speeds to new values
  // Calculate unit change and scale to pwm speed range (0-255)
  if (left >= current_speeds[LEFT]) 
    linc = (map(left,-100,100,-255,255) - map(current_speeds[LEFT],-100,100,-255,255)) / num_units;
  else
    linc = (map(current_speeds[LEFT],-100,100,-255,255) - map(left,-100,100,-255,255)) / -num_units;
  if (right >= current_speeds[RIGHT]) 
    rinc = (map(right,-100,100,-255,255) - map(current_speeds[RIGHT],-100,100,-255,255)) / num_units;
  else 
    rinc = (map(current_speeds[RIGHT],-100,100,-255,255) - map(right,-100,100,-255,255)) / -num_units;

  // Since the motor pwm control is unsigned, we need to convert the speed pwm value to an unsigned value
  ltmp = abs(current_speeds[LEFT]);                               
  rtmp = abs(current_speeds[RIGHT]);
  for (indx = 0; indx < num_units; indx++)
  {
    // Increment/decrement the speed by the calculated unit
    ltmp += linc;                                                 
    rtmp += rinc;
    //Serial.print("Left motors speed: ");
    //Serial.println(ltmp);
    //Serial.print("Right motors speed: ");
    //Serial.println(rtmp);
    //Serial.println(" ");
    // Set the new motor speeds in a pattern to avoid veering the robot
    BckLft.setSpeed(ltmp);
    BckRgt.setSpeed(rtmp);
    FrtLft.setSpeed(ltmp);
    FrtRgt.setSpeed(rtmp);
  }
 
  // Before leaving method, update the current speeds to those just set
  current_speeds[LEFT] = left;
  current_speeds[RIGHT] = right;
}

