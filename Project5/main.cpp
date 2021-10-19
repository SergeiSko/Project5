#include "main.h"

#include "Calc.cpp"

//#pragma warning(disable : 4996)

GLshort const sizeMap = 5000;
GLint const windowX = 800, windowY = 800, windowPositionX = 350, windowPositionY = 0;
GLint const halfWindowX = windowX / 2, halfWindowY = windowY / 2; //Pre-calculations
GLint smoothHeight = 8, smoothRivers = 13, smoothTemperature = 3, smoothHumidity = 3,
      maxRandHeight = 26, maxRandRivers = 26, maxRandLocations = 101,
      maxRandTemperature = 25, maxRandHumidity = 25;//smoothing map and number for calculeted points
GLint sizeMassX = 300, sizeMassY = 300, pointSize = 4;
GLfloat heightMap[sizeMap][sizeMap], riversMap[sizeMap][sizeMap], locationsMap[sizeMap][sizeMap],
        temperatureMap[sizeMap][sizeMap], humidityMap[sizeMap][sizeMap];
GLint biomMap[sizeMap][sizeMap];
int seed = system_clock::now().time_since_epoch().count() % 10;
long seed1 = system_clock::now().time_since_epoch().count() % 10;
long seed2 = seed1 + 5;
CalcMap cm;

bool heightShow = true;
bool riversShow = true;
bool locationsShow = true;
bool multitradingOn = true;
bool ReleaseMap = false;

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
  if(ReleaseMap)
    for (int i = 0; i < windowX/pointSize; i++) {
      for (int j = 0; j < windowY/pointSize; j++) {
        if (true)
          if (riversShow && riversMap[i][j] >= 0.610 && riversMap[i][j] <= 0.625 
            && heightMap[i][j] > 0.55 && heightMap[i][j] < 0.65) glColor3d(0.1f, 0.1f, 1.0f);//add rivers on map
          else if (heightMap[i][j] < 0.62 && heightMap[i][j] > 0.59 && locationsMap[i][j] == 1) glColor3d(1.0f, 0.0f, 1.0f);//locations
          else if (heightMap[i][j] > 0.70) glColor3d(0.0f, 0.0f, 0.8f);//add dark water
          else if (heightMap[i][j] > 0.65) glColor3d(0.0f, 0.0f, 1.0f);//water
          else if (heightMap[i][j] >= 0.62 && heightMap[i][j] <= 0.65) glColor3d(1.0f, 1.0f, 0.0f);//sand
          else if (heightMap[i][j] < 0.62 && heightMap[i][j] > 0.59) glColor3d(0.0f, 1.0f, 0.0f);//main plain
          else if (heightMap[i][j] < 0.59 && heightMap[i][j] > 0.55) glColor3d(0.0f, 0.8f, 0.0f);//high plain
          else if (heightMap[i][j] <= 0.55) glColor3d(1.0f, 1.0f, 1.0f);//hill
        glVertex3d(i * pointSize + (pointSize/2), j * pointSize + (pointSize/2)/*поправка установки точки относительно размера*/, 0);
      }
    }
  else
    for (int i = 0; i < windowX / pointSize; i++) {
      for (int j = 0; j < windowY / pointSize; j++) {
        glColor3d(colorBiom[biomMap[i][j]][0], colorBiom[biomMap[i][j]][1], colorBiom[biomMap[i][j]][2]);
        glVertex3d(i * pointSize + (pointSize / 2), j * pointSize + (pointSize / 2)/*поправка установки точки относительно размера*/, 0);
      }
    }
  glEnd();
}


void draw() {
  glClear(GL_COLOR_BUFFER_BIT);
  int cores_count = thread::hardware_concurrency();
  unsigned int start_time = clock();
  if (multitradingOn&&cores_count >= 2) {
    thread t1(CalcMap::calcTemperatureMap, sizeMassX, sizeMassY, ref(temperatureMap), maxRandTemperature, smoothTemperature);
    thread t2(CalcMap::calcHumidityMap, sizeMassX, sizeMassY, ref(humidityMap), maxRandHumidity, smoothHumidity);
    thread t3(CalcMap::calcHeightMap, sizeMassX, sizeMassY, ref(heightMap), maxRandHeight, smoothHeight);
    thread t4(CalcMap::calcRiversMap, sizeMassX, sizeMassY, ref(riversMap), maxRandRivers, smoothRivers);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    thread t5(CalcMap::calcLocationsMap, sizeMassX, sizeMassY, ref(locationsMap), maxRandLocations);
    thread t6([temperatureMap, humidityMap, biomMap, sizeMassX, sizeMassY]
      { CalcMap::calcBiomMap(temperatureMap, humidityMap, biomMap, sizeMassX, sizeMassY); });
    t5.join();
    t6.join();
  }
  else
  {
    cm.calcTemperatureMap(sizeMassX, sizeMassY, ref(temperatureMap), maxRandTemperature, smoothTemperature);
    cm.calcHumidityMap(sizeMassX, sizeMassY, ref(humidityMap), maxRandHumidity, smoothHumidity);
    cm.calcHeightMap(sizeMassX, sizeMassY, ref(heightMap), maxRandHeight, smoothHeight);
    cm.calcRiversMap(sizeMassX, sizeMassY, ref(riversMap), maxRandRivers, smoothRivers);
  }
    printf("================= Calculate map - %d=================\n", clock() - start_time);
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