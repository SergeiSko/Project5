#include <GL\glut.h>
#include "Source.h"

#pragma warning(disable : 4996)

GLshort const sizeMap = 5000;
GLint const windowX = 800, windowY = 800, windowPositionX = 250, windowPositionY = 0;
GLint const halfSizeX = windowX / 2, halfSizeY = windowY / 2; //Simplification of calculations
GLint smoothHeight = 8, smoothRivers = 17, maxRandHeight = 26, maxRandRivers = 24;//smoothing map and number for calculeted points
GLint sizeMassX = 300, sizeMassY = 300, pointSize = 3;
GLfloat heightMap[sizeMap][sizeMap], riversMap[sizeMap][sizeMap];

void init() {
  glClearColor(0.0, 0.0, 0.0, 0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, 600, 0, 600);
}

void smoothing2d(int count, GLfloat (&massMap)[sizeMap][sizeMap]) {
  float temp;
  while (count > 0)
  {
    for (int i = 0; i < sizeMassX; i++) {//vertical processing
      for (int j = 1; j < sizeMassY - 1; j++) {
        temp = (massMap[i][j-1] + massMap[i][j+1]) / 2;//simplification of calculations 
        if (temp < massMap[i][j])//if the arithmetic mean of neighboring pixels is less
          massMap[i][j] -= massMap[i][j] - temp;//subtract the arithmetic mean of neighboring pixels from the current pixel 
        else
          massMap[i][j] += temp - massMap[i][j];//subtract the current pixel from the arithmetic mean of neighboring pixels
      }
    }
    for (int i = 1; i < sizeMassX - 1; i++) {//horizontal processing
      for (int j = 0; j < sizeMassY; j++) {
        temp = (massMap[i-1][j] + massMap[i+1][j]) / 2;
        if (temp < massMap[i][j])
          massMap[i][j] -= massMap[i][j] - temp;
        else
          massMap[i][j] += temp - massMap[i][j];
      }
    }
    count--;
  }
  if(false)
  for (int i = 0; i < sizeMassX; i++) {
    for (int j = 0; j < sizeMassY; j++) {
      printf("%1.2f ", massMap[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

void calcHeightMap() {
  unsigned int start_time = clock();
  float optimayz = 327670 / maxRandHeight;
  for (int i = 0; i < sizeMassX; i++) {
    for (int j = 0; j < sizeMassY; j++) {
      heightMap[i][j] = rand() / (32767 / maxRandHeight);
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
  smoothing2d(smoothHeight, heightMap);
}

void drawMap() {
  glViewport(2, 2, 800, 800);
  glPointSize(pointSize);
  glBegin(GL_POINTS);
  if(true)
  for (int i = 0; i < sizeMassX; i++) {
    for (int j = 0; j < sizeMassY; j++) {
      if (true)
        if (riversMap[i][j] >= 0.565 && riversMap[i][j] <= 0.575 && heightMap[i][j] > 0.55 && heightMap[i][j] < 0.65) glColor3d(0.1f, 0.1f, 1.0f);
        else if (heightMap[i][j] > 0.70) glColor3d(0.0f, 0.0f, 0.8f);
        else if (heightMap[i][j] > 0.65) glColor3d(0.0f, 0.0f, 1.0f);
        else if (heightMap[i][j] >= 0.62 && heightMap[i][j] <= 0.65) glColor3d(1.0f, 1.0f, 0.0f);
        else if (heightMap[i][j] < 0.62 && heightMap[i][j] > 0.59) glColor3d(0.0f, 1.0f, 0.0f);
        else if (heightMap[i][j] < 0.59 && heightMap[i][j] > 0.55) glColor3d(0.0f, 0.8f, 0.0f);
        else if (heightMap[i][j] <= 0.55) glColor3d(1.0f, 1.0f, 1.0f);
      glVertex3d(i * pointSize + (pointSize/2), j * pointSize + (pointSize/2), 0);
    }
  }
  if(false)
    for (int i = 0; i < sizeMassX; i++) {
      for (int j = 0; j < sizeMassY; j++) {
        if (riversMap[i][j] >= 0.565 && riversMap[i][j] <= 0.575)
          glColor3d(0.f, 0.f, 1.f);
        else
          glColor3d(riversMap[i][j], riversMap[i][j], riversMap[i][j]);
        glVertex3d(i * pointSize, j * pointSize, 0);
      }
    }
  glEnd();
}

void calcRiversMap() {
  GLfloat temp;
  for (int i = 0; i < sizeMassX; i++) {
    for (int j = 0; j < sizeMassY; j++) {
      riversMap[i][j] = rand() / (32767 / maxRandRivers);
      riversMap[i][j] = (int)riversMap[i][j];
      //printf("%f\n", heightMap[i][j]);
      if (riversMap[i][j] / 10 >= 1)
      {
        riversMap[i][j] = 1;
      }
      else
      {
        riversMap[i][j] = 0;
      }
    }
  }
  smoothing2d(smoothRivers, riversMap);
}

void draw() {
  glClear(GL_COLOR_BUFFER_BIT);

  calcHeightMap();
  calcRiversMap();
  drawMap();
  glutSwapBuffers();//show colculated draw function
}

void processNormalKeys(unsigned char key, int x, int y) {
  if (key == 'w')
  {
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