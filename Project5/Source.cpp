#include <GL\glut.h>
#include "Source.h"

#pragma warning(disable : 4996)

GLshort const sizeMap2d = 5000;
GLint const windowX = 800, windowY = 800, windowPositionX = 250, windowPositionY = 0;
GLint const halfSizeX = windowX / 2, halfSizeY = windowY / 2; //Simplification of calculations
GLint smoothing = 8, maxRand = 26;//smoothing map and number for calculeted points
GLint sizeMassX = 500, sizeMassY = 500, pointSize = 3;
GLfloat heightMap[sizeMap2d][sizeMap2d], riversMap[sizeMap2d][sizeMap2d];

void init() {
  glClearColor(0.0, 0.0, 0.0, 0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, 600, 0, 600);
}

void smoothing2d(int count) {
  float temp;
  while (count > 0)
  {
    for (int i = 0; i < sizeMassX; i++) {//vertical processing
      for (int j = 1; j < sizeMassY - 1; j++) {
        temp = (heightMap[i][j-1] + heightMap[i][j+1]) / 2;//simplification of calculations 
        if (temp < heightMap[i][j])//if the arithmetic mean of neighboring pixels is less
          heightMap[i][j] -= heightMap[i][j] - temp;//subtract the arithmetic mean of neighboring pixels from the current pixel 
        else
          heightMap[i][j] += temp - heightMap[i][j];//subtract the current pixel from the arithmetic mean of neighboring pixels
      }
    }
    for (int i = 1; i < sizeMassX - 1; i++) {//horizontal processing
      for (int j = 0; j < sizeMassY; j++) {
        temp = (heightMap[i-1][j] + heightMap[i+1][j]) / 2;
        if (temp < heightMap[i][j])
          heightMap[i][j] -= heightMap[i][j] - temp;
        else
          heightMap[i][j] += temp - heightMap[i][j];
      }
    }
    count--;
  }
  if(false)
  for (int i = 0; i < sizeMassX; i++) {
    for (int j = 0; j < sizeMassY; j++) {
      printf("%1.2f ", heightMap[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

void calcHeightMap() {
  unsigned int start_time = clock();
  float optimayz = 327670 / maxRand;
  for (int i = 0; i < sizeMassX; i++) {
    for (int j = 0; j < sizeMassY; j++) {
      heightMap[i][j] = rand() / (32767 / maxRand);
      heightMap[i][j] = (int)heightMap[i][j];
      //printf("%f\n", heightMap[i][j]);
      if (heightMap[i][j]/10 >= 1)
      {
        heightMap[i][j] = 1;
      }
      else
      {
        heightMap[i][j] = 0;
      }
      //heightMap[i][j] = heightMap[i][j] / 10;
    }
  }
  printf("Calculate HeightMap - %d", clock() - start_time);
}

void drawMap() {
  glViewport(2, 2, 800, 800);
  glPointSize(pointSize);
  glBegin(GL_POINTS);
  for (int i = 0; i < sizeMassX; i++) {
    for (int j = 0; j < sizeMassY; j++) {
      if (true)
        if (heightMap[i][j] < 0.6) glColor3d(0.0f, 1.0f, 0.0f);
        else if (heightMap[i][j] >= 0.6 && heightMap[i][j] <= 0.65) glColor3d(1.0f, 1.0f, 0.0f);
        else if (heightMap[i][j] > 0.65) glColor3d(0.0f, 0.0f, 1.0f);
        else if (heightMap[i][j] == 3) glColor3d(0.9f, 0.0f, 0.0f);
        else glColor3d(0.8f + heightMap[i][j], 0.8f + heightMap[i][j], 0.8f + heightMap[i][j]);
      glVertex3d(i * pointSize, j * pointSize, 0);
    }
  }
  glEnd();
}

void calcRiversMap() {
  GLfloat temp;
  for (int i = 0; i < sizeMassX; i++) {
    for (int j = 0; j < sizeMassY; j++) {
      temp = rand() / (32767 / maxRand);

      temp = (int)temp/10;
      //printf("%f\n", temp);
      if (temp >= 0) heightMap[i][j] = 3;
    }
  }
}

void draw() {
  glClear(GL_COLOR_BUFFER_BIT);

  calcHeightMap();
  calcRiversMap();
  smoothing2d(smoothing);
  drawMap();
  glutSwapBuffers();//show colculated draw function
}

void processNormalKeys(unsigned char key, int x, int y) {
  if (key == 'w')
  {
    calcHeightMap();
    draw();
  }
}

int main(int argc, char** argv) {
  if(true)
  {
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