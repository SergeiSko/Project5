#include "main.h"

class Mobs {
private:
  const static int sizeMap = 5000;
public:
  void spawnMob() {
    thread t1();
  }

  void static moveMob(GLint(&mobMap)[sizeMap][sizeMap], GLint(&x), GLint(&y), GLint(&moveY), GLint(&moveX))
  {
    while (moveX != 0 || moveY != 0)
    {
      mobMap[x][y] = 0;
      if (moveX > 0) {
        x++;
        moveX--;
      }
      else if (moveX < 0)
      {
        x--;
        moveX++;
      }
      if (moveY > 0) {
        y++;
        moveY--;
      }
      else if (moveY < 0)
      {
        y--;
        moveY++;
      }
      mobMap[x][y] = 1;
      Sleep(400);
    }
  }

  void static mob(GLint(&mobMap)[sizeMap][sizeMap], GLfloat(&heightMap)[sizeMap][sizeMap], GLint(&x), GLint(&y)) {
    int moveX;
    int moveY;
    for (;;) {
      moveX = (int)rand()*(10.f / 32767.f) - 5;
      moveY = (int)rand()*(10.f / 32767.f) - 5;
      if(heightMap[x+moveX][y+moveY] > 0.55)
      for (; moveY > 0 && moveY > 0;) {
        moveMob(ref(mobMap), ref(x), ref(y), ref(moveX), ref(moveY));
      }
      Sleep(rand()*(200.f / 32767.f) + 200);
    }
  }

  void static mob2() {
    
  }
};
