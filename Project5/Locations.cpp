#include "main.h"

class Locations {
private:
  static short const sizeMap = 5000;
public:
  static void setLocation(GLfloat(&massMap)[sizeMap][sizeMap], GLint x, GLint y) {
    massMap[x][y] = 1;
    massMap[x+1][y] = 1;
    massMap[x][y+1] = 1;
    massMap[x-1][y] = 1;
    massMap[x][y-1] = 1;
  }


};