// WhipperSnapper
// copyright 2017 by Walter Anderson

#include "Robot.h"

Robot Whippersnapper;

void setup() {
  //Serial.begin(9600);

  // Pause the initialize for a second, to give time to place bot
  delay(1000);
  
  // Start moving forward
  Whippersnapper.move(100,100);
}

void loop() {
  int tst;
  tst = Whippersnapper.bumpers();

  // If the bumpers are triggered then stop the robot
  if (tst > 0)
    Whippersnapper.stop();

  switch(tst) {
    case 8:     // Front left bumper triggered
    case 4:     // Front Right bumper triggered
    case 12:    // Both front bumpers triggered
      Whippersnapper.move(-100,-100);             // Backup
      Whippersnapper.move(0,0);                   // Stop
      Whippersnapper.move(-50,50);                // Turn left
      Whippersnapper.stop();                      // Quick stop
      Whippersnapper.move(100,100);               // Proceed forward again
      break;
  }
}
