#include "main.h"

#include "Calc.cpp"
#include "Mobs.cpp"
#include "Controller.cpp"


//#pragma warning(disable : 4996)

GLshort const sizeMap = 5000;// size of massive

GLint const windowX = 800, windowY = 800, windowPositionX = 350, windowPositionY = 0;
GLint const halfWindowX = windowX / 2, halfWindowY = windowY / 2; //Pre-calculations

GLint smoothHeight = 8, smoothRivers = 13, smoothTemperature = 5, smoothHumidity = 5,
      maxRandHeight = 26, maxRandRivers = 26, maxRandLocations = 101,
      maxRandTemperature = 25, maxRandHumidity = 25;//smoothing map and number for calculeted points

GLfloat sizeMassX = 1000, sizeMassY = 1000, pointSize = 3;

//-------------Maps------------
GLfloat heightMap[sizeMap][sizeMap], riversMap[sizeMap][sizeMap], locationsMap[sizeMap][sizeMap],
        temperatureMap[sizeMap][sizeMap], humidityMap[sizeMap][sizeMap];
GLint biomMap[sizeMap][sizeMap];
GLint mobMap[sizeMap][sizeMap];
GLfloat newMap[sizeMap][sizeMap];

GLint mobX = 88, mobY = 133;

int seed = system_clock::now().time_since_epoch().count() % 10;
long seed1 = system_clock::now().time_since_epoch().count() % 10;
long seed2 = seed1 + 5;

GLshort fps = 0, lockFPS = 60;

bool withLockFPS = true, counterFPS = true;
bool heightShow = true;
bool riversShow = true;
bool locationsShow = true;
bool multitradingOn = true;
bool ReleaseMap = true;

//----------Player------------
bool player = true;
GLfloat speed = 0.02;
GLfloat playerX = 0, playerY = 0;//  player position
GLfloat playerSizeX, playerSizeY;//  player size

void init() {
  glClearColor(0.0, 0.0, 0.0, 0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, 600, 0, 600);
}

static void spawnMob(float x, float y) {
  GLfloat a1, a2, a3, a4;
  glViewport(x, y, 50, 50);
  glBegin(GL_POLYGON);
  glVertex3f(0, 0, 0);
  glVertex3f(0, 50, 0);
  glVertex3f(50, 0, 0);
  glVertex3f(50, 50, 0);
  glEnd();
}

void static drawMap() {
  glViewport(2, 2, 800, 800);
  glPointSize(pointSize);
  glBegin(GL_POINTS);
  if(ReleaseMap)
    for (int i = 0; i < windowX/pointSize; i++) {
      for (int j = 0; j < windowY/pointSize; j++) {
        if (true)
          if (locationsMap[i][j] == 1 && false) spawnMob(i * pointSize + (pointSize / 2), j * pointSize + (pointSize / 2));
          if (riversShow && riversMap[i][j] >= 0.610 && riversMap[i][j] <= 0.625 
            && heightMap[i][j] > 0.55 && heightMap[i][j] < 0.65) glColor3f(0.1f, 0.1f, 1.0f);//add rivers on map
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
        glColor3f(newMap[i][j], newMap[i][j], newMap[i][j]);
        //glColor3d(colorBiom[biomMap[i][j]][0], colorBiom[biomMap[i][j]][1], colorBiom[biomMap[i][j]][2]);
        glVertex3d(i * pointSize + (pointSize / 2), j * pointSize + (pointSize / 2)/*поправка установки точки относительно размера*/, 0);
      }
    }
  glEnd();
}

void calcMap() {
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
    /*thread t5(CalcMap::getTemperatureMap, temperatureMap, sizeMassX, sizeMassY);
    thread t6(CalcMap::getHumidityMap, humidityMap, sizeMassX, sizeMassY);
    t5.join();
    t6.join();*/
    thread t7(CalcMap::calcLocationsMap, sizeMassX, sizeMassY, ref(locationsMap), maxRandLocations);
    thread t8(CalcMap::calcBiomMap, sizeMassX, sizeMassY, ref(biomMap), ref(temperatureMap), ref(humidityMap));//problem biom map
    //thread t9(Mobs::mob, ref(mobMap), ref(heightMap), ref(mobX), ref(mobY));//mob moving on grid map
    t7.join();
    t8.join();
    //t9.detach();
  }
  else
  {
    CalcMap::calcTemperatureMap(sizeMassX, sizeMassY, ref(temperatureMap), maxRandTemperature, smoothTemperature);
    CalcMap::calcHumidityMap(sizeMassX, sizeMassY, ref(humidityMap), maxRandHumidity, smoothHumidity);
    CalcMap::calcHeightMap(sizeMassX, sizeMassY, ref(heightMap), maxRandHeight, smoothHeight);
    CalcMap::calcRiversMap(sizeMassX, sizeMassY, ref(riversMap), maxRandRivers, smoothRivers);
  }
  printf("================= Calculate map - %d=================\n", clock() - start_time);
}

void drawPlayer() {
  glViewport(halfWindowX - 100 + playerX, halfWindowY - 100 + playerY, 100, 100);
  glBegin(GL_QUADS);
  glColor3f(1.f, 0.f, 0.f);
  glVertex2f(0, 0);
  glColor3f(0.f, 1.f, 0.f);
  glVertex2f(600, 0);
  glColor3f(0.f, 0.f, 1.f);
  glVertex2f(600, 600);
  glColor3f(1.f, 1.f, 0.f);
  glVertex2f(0, 600);
  glEnd();
}

void draw() {
  int startTime = clock();
  glClear(GL_COLOR_BUFFER_BIT);
  drawMap();
  drawPlayer();
  glutSwapBuffers();//show colculated draw function
  fps++;

  while ((clock() - startTime < 1000/lockFPS)&&withLockFPS)
  {
    Sleep(2);
  }
}

void checkFPS() {
  for (;;)
  {
    printf("FPS: %d\n", fps);
    fps = 0;
    Sleep(1000);
  }
}

int main(int argc, char** argv) {
  calcMap();
  thread t = thread(Controller::control, ref(speed), ref(playerX), ref(playerY));
  if (counterFPS)thread t(checkFPS); t.join();
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE | GLUT_STENCIL | GLUT_ACCUM);
  glutInitWindowSize(windowX, windowY);
  glutInitWindowPosition(windowPositionX, windowPositionY);
  glutCreateWindow("Graphics");
  init();
  //glutDisplayFunc(draw);
  glutIdleFunc(draw);
  glutMainLoop();
}