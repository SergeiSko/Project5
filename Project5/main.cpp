#include <GL\glut.h>
#include "main.h"

//#pragma warning(disable : 4996)

GLshort const sizeMap = 5000;
GLint const windowX = 800, windowY = 800, windowPositionX = 350, windowPositionY = 0;
GLint const halfWindowX = windowX / 2, halfWindowY = windowY / 2; //Pre-calculations
GLfloat smoothHeight = 8, smoothRivers = 10, smoothTemperature = 3, smoothHumidity = 3,
        maxRandHeight = 26, maxRandRivers = 22,
        maxRandTemperature = 25, maxRandHumidity = 25;//smoothing map and number for calculeted points
GLint sizeMassX = 2000, sizeMassY = 2000, pointSize = 3;
GLfloat heightMap[sizeMap][sizeMap], riversMap[sizeMap][sizeMap], locationsMap[sizeMap][sizeMap],
        temperatureMap[sizeMap][sizeMap], humidityMap[sizeMap][sizeMap];
int seed = system_clock::now().time_since_epoch().count() % 10;
CalcMap cm;

using namespace std;
using namespace chrono;

void init() {
  glClearColor(0.0, 0.0, 0.0, 0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, 600, 0, 600);
}

void static drawMap() {
  glViewport(2, 2, 800, 800);
  glPointSize(pointSize);
  glBegin(GL_POINTS);
  if(true)
  for (int i = 0; i < windowX/pointSize; i++) {
    for (int j = 0; j < windowY/pointSize; j++) {
      if (true)
        if (riversMap[i][j] >= 0.585 && riversMap[i][j] <= 0.595 
          && heightMap[i][j] > 0.55 && heightMap[i][j] < 0.65) glColor3d(0.1f, 0.1f, 1.0f);//add rivers on map
        else if (heightMap[i][j] > 0.70) glColor3d(0.0f, 0.0f, 0.8f);//add dark water
        else if (heightMap[i][j] > 0.65) glColor3d(0.0f, 0.0f, 1.0f);//water
        else if (heightMap[i][j] >= 0.62 && heightMap[i][j] <= 0.65) glColor3d(1.0f, 1.0f, 0.0f);//sand
        else if (heightMap[i][j] < 0.62 && heightMap[i][j] > 0.59) glColor3d(0.0f, 1.0f, 0.0f);//main plain
        else if (heightMap[i][j] < 0.59 && heightMap[i][j] > 0.55) glColor3d(0.0f, 0.8f, 0.0f);//high plain
        else if (heightMap[i][j] <= 0.55) glColor3d(1.0f, 1.0f, 1.0f);//hill
      glVertex3d(i * pointSize + (pointSize/2), j * pointSize + (pointSize/2)/*поправка установки точки относительно размера*/, 0);
    }
  }
  if(false)//для тестирования отдельной генерации
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


void draw() {
  glClear(GL_COLOR_BUFFER_BIT);
  srand(seed);
  unsigned int start_time = clock();

  thread t1(cm.calcTemperatureMap, sizeMassX, sizeMassY, ref(temperatureMap), maxRandTemperature, smoothTemperature);
  thread t2(cm.calcHumidityMap, sizeMassX, sizeMassY, ref(humidityMap), maxRandHumidity, smoothHumidity);
  thread t3(cm.calcHeightMap, sizeMassX, sizeMassY, ref(heightMap), maxRandHeight, smoothHeight);
  thread t4(cm.calcRiversMap, sizeMassX, sizeMassY, ref(riversMap), maxRandRivers, smoothRivers);
  t1.join();
  t2.join();
  t3.join();
  t4.join();
  printf("Calculate map - %d\n", clock() - start_time);
  drawMap();
  glutSwapBuffers();//show colculated draw function
}

void processNormalKeys(unsigned char key, int x, int y) {
  if (key == 'w')
  { draw(); }
  else if (key == 'a')
  { draw(); }
  else if (key == 's')
  { draw(); }
  else if (key == 'd')
  { draw(); }
}

int main(int argc, char** argv) {
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