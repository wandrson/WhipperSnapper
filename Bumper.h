// copyright 2017 by Walter Anderson
#ifndef _Bumper_h_
#define _Bumper_h_

class Bumper
{
  public:
    Bumper(int fl, int fr, int bl, int br);
    int status(void);

  private:
    int frtlft;
    int frtrgt;
    int bcklft;
    int bckrgt;
};

#endif
