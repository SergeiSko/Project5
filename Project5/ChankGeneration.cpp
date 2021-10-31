#include "main.h"

class ChankGeneration
{
public:
  static int binarRand(int maxRand) 
  {
    float number = rand() * ((GLfloat)maxRand / 32767);
    number = (int)number;
    if (number / 10 >= 1)
    {
      return 1;
    }
    else
    {
      return 0;
    }
  }
  static void generationMap(GLfloat(&massMap)[sizeMass][sizeMass], GLfloat(&sizeX), GLfloat(&sizeY), GLint(&maxRand)) 
  {
    for(int i = 0; i < sizeX; i++)
      for (int j = 0; j < sizeY; j++)
      {
        massMap[i][j] = binarRand(maxRand);
      }
  }

  static void chunkSmuthing(GLfloat(&massMap)[sizeMass][sizeMass], GLint (&x), GLint(&y), GLint smuthing)
  {
    float temp;
    while (smuthing > 0)
    {
      for (int i = 0; i < 8; i++) {//vertical processing
        for (int j = 0; j < 8; j++) {
          temp = (massMap[x + i][y + j - 1] + massMap[i][j + 1]) / 2;//simplification of calculations 
          if (temp < massMap[x + i][y + j])//if the arithmetic mean of neighboring pixels is less
            massMap[x + i][y + j] -= massMap[x + i][y + j] - temp;//subtract the arithmetic mean of neighboring pixels from the current pixel 
          else
            massMap[x + i][y + j] += temp - massMap[x + i][y + j];//subtract the current pixel from the arithmetic mean of neighboring pixels
        }
      }
      for (int i = 0; i < 8; i++) {//horizontal processing
        for (int j = 0; j < 8; j++) {
          temp = (massMap[x + i - 1][y + j] + massMap[i + 1][j]) / 2;
          if (temp < massMap[x + i][y + j])
            massMap[x + i][y + j] -= massMap[x + i][y + j] - temp;
          else
            massMap[x + i][y + j] += temp - massMap[x + i][y + j];
        }
      }
      smuthing--;
    }
  }

  static void mapSmuthing(GLfloat(&massMap)[sizeMass][sizeMass], GLfloat(&sizeX), GLfloat(&sizeY), GLint(&smuthing))
  {
    for (int i = 1; i < sizeX; i+=7)
      for (int j = 1; j < sizeY; j+=7)
      {
        chunkSmuthing(massMap, i, j, smuthing);
      }
  }
};