#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <iostream>
#include <math.h>
#include <malloc.h>
#include <time.h>
#include <ctime>
#include <chrono>
#include <random>
#include <thread>
#include <limits.h>
#include <random>

//#pragma warning(disable : 4996)

using namespace std;
using namespace chrono;

class CalcMap {
private:
  short static const sizeMap = 5000;
public:
  int static binarRand(float maxRand) {
    GLfloat number = rand() * (maxRand / 32767);
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

public:
  int static newBinarRand(float maxRand, unsigned int seed) {
    //srandom(seed);
    //unsigned int number = random();
    return 0;
  }

  void static smoothMap(int count, GLfloat(&massMap)[sizeMap][sizeMap], GLint sizeMassX, GLint sizeMassY) {
    float temp;
    while (count > 0)
    {
      for (int i = 0; i < sizeMassX; i++) {//vertical processing
        for (int j = 1; j < sizeMassY - 1; j++) {
          temp = (massMap[i][j - 1] + massMap[i][j + 1]) / 2;//simplification of calculations 
          if (temp < massMap[i][j])//if the arithmetic mean of neighboring pixels is less
            massMap[i][j] -= massMap[i][j] - temp;//subtract the arithmetic mean of neighboring pixels from the current pixel 
          else
            massMap[i][j] += temp - massMap[i][j];//subtract the current pixel from the arithmetic mean of neighboring pixels
        }
      }
      for (int i = 1; i < sizeMassX - 1; i++) {//horizontal processing
        for (int j = 0; j < sizeMassY; j++) {
          temp = (massMap[i - 1][j] + massMap[i + 1][j]) / 2;
          if (temp < massMap[i][j])
            massMap[i][j] -= massMap[i][j] - temp;
          else
            massMap[i][j] += temp - massMap[i][j];
        }
      }
      count--;
    }
    if (false)
      for (int i = 0; i < sizeMassX; i++) {
        for (int j = 0; j < sizeMassY; j++) {
          printf("%1.2f ", massMap[i][j]);
        }
        printf("\n");
      }
    printf("\n");
  }

  void static calcTemperatureMap(GLint const sizeMassX, GLint const sizeMassY, GLfloat(&massMap)[sizeMap][sizeMap], GLfloat maxRand, GLfloat smooth) {
    unsigned int start_time = clock();
    for (int i = 0; i < sizeMassX; i++) {
      for (int j = 0; j < sizeMassY; j++) {
        massMap[i][j] = binarRand(maxRand);
      }
    }
    smoothMap(smooth, massMap, sizeMassX, sizeMassY);
    printf("Calculate TemperatureMap - %d\n", clock() - start_time);
  }

  void static calcHumidityMap(GLint sizeMassX, GLint sizeMassY, GLfloat(&massMap)[sizeMap][sizeMap], GLfloat maxRand, GLfloat smooth) {
    unsigned int start_time = clock();
    for (int i = 0; i < sizeMassX; i++) {
      for (int j = 0; j < sizeMassY; j++) {
        massMap[i][j] = binarRand(maxRand);
      }
    }
    smoothMap(smooth, massMap, sizeMassX, sizeMassY);
    printf("Calculate HumidityMap - %d\n", clock() - start_time);
  }

  void static calcLocationMap(GLint sizeMassX, GLint sizeMassY, GLfloat(&massMap)[sizeMap][sizeMap], GLfloat maxRand, GLfloat smooth) {
    unsigned int start_time = clock();
    for (int i = 0; i < sizeMassX; i++) {
      for (int j = 0; j < sizeMassY; j++) {
        massMap[i][j] = binarRand(maxRand);
      }
    }
    smoothMap(smooth, massMap, sizeMassX, sizeMassY);
    printf("Calculate HumidityMap - %d\n", clock() - start_time);
  }

  void static calcHeightMap(GLint sizeMassX, GLint sizeMassY, GLfloat(&massMap)[sizeMap][sizeMap], GLfloat maxRand, GLfloat smooth) {
    unsigned int start_time = clock();
    srand(152512);
    for (int i = 0; i < sizeMassX; i++) {
      for (int j = 0; j < sizeMassY; j++) {
        massMap[i][j] = binarRand(maxRand);
      }
    }
    smoothMap(smooth, massMap, sizeMassX, sizeMassY);
    printf("Calculate HeightMap - %d\n", clock() - start_time);
  }

  void static calcRiversMap(GLint sizeMassX, GLint sizeMassY, GLfloat(&massMap)[sizeMap][sizeMap], GLfloat maxRand, GLfloat smooth) {
    unsigned int start_time = clock();
    srand(759238);
    for (int i = 0; i < sizeMassX; i++) {
      for (int j = 0; j < sizeMassY; j++) {

        massMap[i][j] = binarRand(maxRand);
      }
    }
    smoothMap(smooth, massMap, sizeMassX, sizeMassY);
    printf("Calculate RiversMap - %d\n", clock() - start_time);
  }
  void threadCalcTemperatureMap(GLint const sizeMassX, GLint const sizeMassY, GLfloat(&massMap)[sizeMap][sizeMap], GLfloat maxRand, GLfloat smooth)
  {
    thread t(calcTemperatureMap, sizeMassX, sizeMassY, ref(massMap), maxRand, smooth);
    t.join();
  }
  void threadCalcHumidityMap(GLint const sizeMassX, GLint const sizeMassY, GLfloat(&massMap)[sizeMap][sizeMap], GLfloat maxRand, GLfloat smooth)
  {
    thread t(calcHumidityMap, sizeMassX, sizeMassY, ref(massMap), maxRand, smooth);
    t.join();
  }
  void threadCalcHeightMap(GLint const sizeMassX, GLint const sizeMassY, GLfloat(&massMap)[sizeMap][sizeMap], GLfloat maxRand, GLfloat smooth)
  {
    thread t(calcHeightMap, sizeMassX, sizeMassY, ref(massMap), maxRand, smooth);
    t.join();
  }
  void threadCalcRiversMap(GLint const sizeMassX, GLint const sizeMassY, GLfloat(&massMap)[sizeMap][sizeMap], GLfloat maxRand, GLfloat smooth)
  {
    thread t(calcRiversMap, sizeMassX, sizeMassY, ref(massMap), maxRand, smooth);
    t.join();
  }
};