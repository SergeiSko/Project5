#include <GL\glut.h>
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <malloc.h>
#include <time.h>

#pragma warning(disable : 4996)


GLshort const sizeMap2d = 5000;
GLint const windowX = 800, windowY = 750, windowPositionX = 250, windowPositionY = 10;
GLint const halfSizeX = windowX / 2, halfSizeY = windowY / 2; //Simplification of calculations
GLint smoothing = 8, maxRand = 26;//smoothing map and number for calculeted points
GLint sizeMassX = 350, sizeMassY = 350, pointSize = 4;
GLfloat mass[500], heightMap2d[sizeMap2d][sizeMap2d], riversMap2d[sizeMap2d][sizeMap2d];

void init() {
  glClearColor(0.0, 0.0, 0.0, 0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, 600, 0, 600);
}

void smoothing1d(int count) {
  while (count > 0)
  {
    for (int i = 1; i < sizeMassX; i++)
    {
      if (mass[i] < (mass[i - 1] + mass[i + 1]) / 2)
      {
        mass[i] += ((mass[i - 1] + mass[i + 1]) / 2) - mass[i];
      }
      else
      {
        mass[i] -= mass[i] - ((mass[i - 1] + mass[i + 1]) / 2);
      }
    }
    count--;
  }
}

void smoothing2d(int count) {
  float temp;
  while (count > 0)
  {
    for (int i = 0; i < sizeMassX; i++) {//vertical processing
      for (int j = 1; j < sizeMassY - 1; j++) {
        temp = (heightMap2d[i][j-1] + heightMap2d[i][j+1]) / 2;//simplification of calculations 
        if (temp < heightMap2d[i][j])//if the arithmetic mean of neighboring pixels is less
          heightMap2d[i][j] -= heightMap2d[i][j] - temp;//subtract the arithmetic mean of neighboring pixels from the current pixel 
        else
          heightMap2d[i][j] += temp - heightMap2d[i][j];//subtract the current pixel from the arithmetic mean of neighboring pixels
      }
    }
    for (int i = 1; i < sizeMassX - 1; i++) {//horizontal processing
      for (int j = 0; j < sizeMassY; j++) {
        temp = (heightMap2d[i-1][j] + heightMap2d[i+1][j]) / 2;
        if (temp < heightMap2d[i][j])
          heightMap2d[i][j] -= heightMap2d[i][j] - temp;
        else
          heightMap2d[i][j] += temp - heightMap2d[i][j];
      }
    }
    count--;
  }
  if(false)
  for (int i = 0; i < sizeMassX; i++) {
    for (int j = 0; j < sizeMassY; j++) {
      printf("%1.2f ", heightMap2d[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

void calcLine() {
  for (int i = 0; i <= sizeMassX; i += 4)
  {
    mass[i] = ((int)(rand() / (32767 / maxRand))) / 10;
  }
  for (int i = 2; i < sizeMassX; i += 4) {
    mass[i] = (mass[i-2]+mass[i+2]) / 2;
    mass[i-1] = (mass[i-2]+mass[i]) / 2;
    mass[i+1] = (mass[i]+mass[i+2]) / 2;
  }
  if(false)
  for (int i = 0; i < sizeMassX; i++)
  { 
    printf("%.0f\n", mass[i]);
  }
  smoothing1d(smoothing);
}

void drawLine() {
  glViewport(30, 30, 600, 600);
  glBegin(GL_LINE_STRIP);
  glColor3d(0.0, 1.0, 0.0);
  for (int i = 0; i < sizeMassX; i++) {
    glVertex3d(i * 3, mass[i], 0);
  }
  glEnd();
}

void calcMass2d() {
  for (int i = 0; i < sizeMassX; i++) {
    for (int j = 0; j < sizeMassY; j++) {
      heightMap2d[i][j] = rand() / (32767 / maxRand);
      heightMap2d[i][j] = (int)heightMap2d[i][j];
      //printf("%f\n", heightMap2d[i][j]);
      if (heightMap2d[i][j] / 10 >= 1)
      {
        heightMap2d[i][j] = 1;
      }
      else
      {
        heightMap2d[i][j] = 0;
      }
      //heightMap2d[i][j] = heightMap2d[i][j] / 10;
    }
  }
}

void calcNewMap() {
  for (int i = 0; i < 15; i++)
  {
    for (int j = 0; j < sizeMassX; j++)
    {
      if (true)
      {
        heightMap2d[sizeMassX + i][j] = rand() / (32767 / maxRand);
        heightMap2d[sizeMassX + i][j] = (int)heightMap2d[sizeMassX + i][j];
        if (heightMap2d[sizeMassX + i][j] / 10 >= 1)
        {
          heightMap2d[sizeMassX + i][j] = 1;
        }
        else
        {
          heightMap2d[sizeMassX + i][j] = 0;
        }
      }
    }
  }
  sizeMassX += 15;
  printf("size massX: %d\n size massY: %d\n", sizeMassX, sizeMassY);
}

void drawMass2d() {
  glViewport(30, 30, 600, 600);
  glPointSize(pointSize);
  glBegin(GL_POINTS);
  for (int i = 0; i < sizeMassX; i++) {
    for (int j = 0; j < sizeMassY; j++) {
      if(true)
      if(heightMap2d[i][j] < 0.6) glColor3d(0.0f, 1.0f, 0.0f);
      else if (heightMap2d[i][j] >= 0.6 && heightMap2d[i][j] <= 0.65) glColor3d(1.0f, 1.0f, 0.0f);
      else if (heightMap2d[i][j] > 0.65) glColor3d(0.0f, 0.0f, 1.0f);
        else glColor3d(0.0f + heightMap2d[i][j], 0.0f + heightMap2d[i][j], 0.0f + heightMap2d[i][j]);
      glVertex3d(i*pointSize, j*pointSize, 0);
    }
  }
  glEnd();
}

void draw() {
  glClear(GL_COLOR_BUFFER_BIT);
  if(false)
  {
    calcLine();//function random line calculate
    drawLine();
  }
  //calcMass2d();
  //calcNewMap();
  drawMass2d();
  //Sleep(600);
  glutSwapBuffers();//show colculated draw function
  //scanf_s("%d", &smoothing);
  //printf("<<render of screen>>\n");
}

void processNormalKeys(unsigned char key, int x, int y) {
  if (key == 'w')
  {
    calcMass2d();
    draw();
  }
}

int main(int argc, char** argv) {
  if(true)
  {
    calcMass2d();
    smoothing2d(smoothing);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE | GLUT_STENCIL | GLUT_ACCUM);
    glutInitWindowSize(windowX, windowY);
    glutInitWindowPosition(windowPositionX, windowPositionY);
    glutCreateWindow("Graphics");
    init();
    glutDisplayFunc(draw);
    //glutKeyboardFunc(processNormalKeys);
    //glutIdleFunc(draw);
    glutMainLoop();
  }
}