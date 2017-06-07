// WhipperSnapper
// copyright 2017 by Walter Anderson

#include <Servo.h>
#include "env.h"
#include "Robot.h"

Robot Whippersnapper;

void setup() {
  int pos, indx;
#if defined (DEBUG)
  Serial.begin(9600);
#endif
  // Pause the initialize for a second, to give time to place bot
  delay(250);
  Servo myservo;
  myservo.attach(9);
  for (indx=0; indx<2; indx++) {
    for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(5);                       // waits 15ms for the servo to reach the position
    }
    for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(5);                       // waits 15ms for the servo to reach the position
    }
  }  
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
      Whippersnapper.stop();                   // Stop
      Whippersnapper.move(-100,-100);             // Backup
      delay(500);
      Whippersnapper.move(0,0);                   // Stop
      Whippersnapper.move(-100,100);              // Turn left
      delay(1000);
      Whippersnapper.stop();                      // Quick stop
      Whippersnapper.move(100,100);               // Proceed forward again
      break;
  }
}
