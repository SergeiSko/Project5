#include "main.h"

struct Propertis
{
  short speed = 1;
  long x, y;
  short moveX = 0, moveY = 0;
};

class Mob {
private:

public:
  short speed = 1;
  long x, y;
  short moveX = 0, moveY = 0;
  
  Mob(long x, long y) {
    this->x = x;
    this->y = y;

    //thread t();
  }
  
  void setSpeed(short speed) { this->speed = speed; }
  
  void setPosition(long x, long y) { this->x = x; this->y = y; }

  void static newMoveX(int (&move), short (&speed), long (&x))
  {
    for(int i = 0; i < move; i++) { x++; Sleep((int)1000 / speed); }
  }

  void static newMoveY(int move, short speed, long (&y))
  {
    for (int i = 0; i < move; i++) { y++; Sleep((int)1000 / speed); }
  }
};
