// copyright 2017 by Walter Anderson
#include <Arduino.h>
#include "Bumper.h"

// Constructor
Bumper::Bumper(int fl, int fr, int bl, int br)
{
  frtlft = fl;
  frtrgt = fr;
  bcklft = bl;
  bckrgt = br;
  pinMode(frtlft, INPUT_PULLUP);
  pinMode(frtrgt, INPUT_PULLUP);
  pinMode(bcklft, INPUT_PULLUP);
  pinMode(bckrgt, INPUT_PULLUP);
}

int Bumper::status()
{
  int retVal=0;
  retVal = digitalRead(frtlft);
  retVal = (retVal << 1) | digitalRead(frtrgt);
  retVal = (retVal << 1) | digitalRead(bcklft);
  retVal = (retVal << 1) | digitalRead(bckrgt);
  return(retVal);
}

