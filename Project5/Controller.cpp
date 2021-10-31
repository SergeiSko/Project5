#include "main.h"
#include <winuser.h>
#include <windows.h>



class Controller
{
public:
  static void control(GLfloat(&speed), GLfloat(&playerX), GLfloat(&playerY)) {
    printf("Listen LButton");
    GLfloat count = 1;
    for (;;) {
      if (GetAsyncKeyState(0x57) || GetAsyncKeyState(VK_UP)) {//UP (W or UP)
        playerY += speed;
      }
      if (GetAsyncKeyState(0x41) || GetAsyncKeyState(VK_LEFT)) {//LEFT (A or LEFT)
        playerX -= speed;
      }
      if (GetAsyncKeyState(0x53) || GetAsyncKeyState(VK_DOWN)) {//DOWN (S or DOWN)
        playerY -= speed;
      }
      if (GetAsyncKeyState(0x44) || GetAsyncKeyState(VK_RIGHT)) {//RIGHT (D or RIGHT)
        playerX += speed;
      }
    }
  }


  static void controlKeys(unsigned char key, int x, int y) {//shit
    if (key == 'w')
    {
      
    }
    else if (key == 'a')
    {
      
    }
    else if (key == 's')
    {
      
    }
    else if (key == 'd')
    {
      
    }
  }
};