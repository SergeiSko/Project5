#include "main.h"
#include "Locations.cpp"

class CalcMap {
private:
  short static const sizeMap = 5000;
  Locations ls;
  static GLfloat temperatureMap[sizeMap][sizeMap], humidityMap[sizeMap][sizeMap], biomMap[sizeMap][sizeMap];
public:
  int static binarRand(GLint maxRand) {
    GLfloat number = rand() * ((GLfloat)maxRand / 32767);
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
  int static newBinarRand(GLint maxRand) {
    GLfloat number = rand() * ((GLfloat)maxRand / 32767);
    number = (int)number;
    if (number >= 100)
    {
      return 1;
    }
    else
    {
      return 0;
    }
  }

  int static rand100() {
    return (int) rand() * (100.f / 32767.f);
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

  void static calcBiomMap(GLfloat const sizeMassX, GLfloat const sizeMassY, GLint(&massMap)[sizeMap][sizeMap], 
    GLfloat(&temperatureMap)[sizeMap][sizeMap], GLfloat(&humidityMap)[sizeMap][sizeMap]) {
    for (int i = 0; i < sizeMassX; i++) {
      for (int j = 0; j < sizeMassY; j++) {
        if (temperatureMap[i][j] <= 100.f && temperatureMap[i][j] > 65.f &&//Пустыня
          humidityMap[i][j] >= 0.f && humidityMap[i][j] < 25.f)
          massMap[i][j] = 0;
        else if (temperatureMap[i][j] <= 100.f && temperatureMap[i][j] > 80.f &&//Саванна
          humidityMap[i][j] >= 25.f && humidityMap[i][j] < 50.f)
          massMap[i][j] = 1;
        else if (temperatureMap[i][j] <= 100.f && temperatureMap[i][j] > 80.f &&//Сезонный лес
          humidityMap[i][j] >= 50.f && humidityMap[i][j] < 75.f)
          massMap[i][j] = 2;
        else if (temperatureMap[i][j] <= 100.f && temperatureMap[i][j] > 80.f &&//Дождевый лес
          humidityMap[i][j] >= 75.f && humidityMap[i][j] <= 100.f)
          massMap[i][j] = 3;
        else if (temperatureMap[i][j] <= 80.f && temperatureMap[i][j] > 40.f &&//Болото
          humidityMap[i][j] >= 75.f && humidityMap[i][j] <= 100.f)
          massMap[i][j] = 4;
        else if (temperatureMap[i][j] <= 80.f && temperatureMap[i][j] > 40.f &&//Лес
          humidityMap[i][j] >= 50.f && humidityMap[i][j] < 75.f)
          massMap[i][j] = 5;
        else if (temperatureMap[i][j] <= 80.f && temperatureMap[i][j] > 40.f &&//Деревья
          humidityMap[i][j] >= 25.f && humidityMap[i][j] <= 50.f)
          massMap[i][j] = 6;
        else if (temperatureMap[i][j] <= 40.f && temperatureMap[i][j] > 25.f &&//Тайга
          humidityMap[i][j] >= 25.f && humidityMap[i][j] < 100.f)
          massMap[i][j] = 7;
        else if (temperatureMap[i][j] <= 65.f && temperatureMap[i][j] > 25.f &&//Равнина
          humidityMap[i][j] >= 0.f && humidityMap[i][j] < 25.f)
          massMap[i][j] = 8;
        else if (temperatureMap[i][j] <= 25.f && temperatureMap[i][j] >= 0.f &&//Тундра
          humidityMap[i][j] >= 0.f && humidityMap[i][j] < 100.f)
          massMap[i][j] = 9;
        else {
          massMap[i][j] = 10;
          //printf("---- temperatureMap = %f --- humidityMap = %f ---\n", temperatureMap[i][j], humidityMap[i][j]);
        }
      }
    }
  }

  void static calcTemperatureMap(GLint const sizeMassX, GLint const sizeMassY, GLfloat(&massMap)[sizeMap][sizeMap], GLfloat maxRand, GLint smooth) {
    unsigned int start_time = clock();
    for (int i = 0; i < sizeMassX; i++) {
      for (int j = 0; j < sizeMassY; j++) {
        massMap[i][j] = rand100();
        //printf("%d\n", rand100());
      }
    }
    smoothMap(smooth, massMap, sizeMassX, sizeMassY);
    printf("Calculate TemperatureMap - %d\n", clock() - start_time);
  }

  void static calcHumidityMap(GLint sizeMassX, GLint sizeMassY, GLfloat(&massMap)[sizeMap][sizeMap], GLint maxRand, GLint smooth) {
    unsigned int start_time = clock();
    for (int i = 0; i < sizeMassX; i++) {
      for (int j = 0; j < sizeMassY; j++) {
        massMap[i][j] = rand100();
      }
    }
    smoothMap(smooth, massMap, sizeMassX, sizeMassY);
    printf("Calculate HumidityMap - %d\n", clock() - start_time);
  }

  void static calcLocationsMap(GLint sizeMassX, GLint sizeMassY, GLfloat(&massMap)[sizeMap][sizeMap], GLint maxRand) {
    unsigned int start_time = clock();
    for (int i = 0; i < sizeMassX; i++) {
      for (int j = 0; j < sizeMassY; j++) {
        if (newBinarRand(maxRand) == 1)
          Locations::setLocation(ref(massMap), i, j);
      }
    }
    printf("Calculate LocationsMap - %d\n", clock() - start_time);
  }

  void static calcHeightMap(GLint sizeMassX, GLint sizeMassY, GLfloat(&massMap)[sizeMap][sizeMap], GLint maxRand, GLint smooth) {
    unsigned int start_time = clock();
    srand(13548);
    for (int i = 0; i < sizeMassX; i++) {
      for (int j = 0; j < sizeMassY; j++) {
        massMap[i][j] = binarRand(maxRand);
      }
    }
    smoothMap(smooth, massMap, sizeMassX, sizeMassY);
    printf("Calculate HeightMap - %d\n", clock() - start_time);
  }

  void static calcRiversMap(GLint sizeMassX, GLint sizeMassY, GLfloat(&massMap)[sizeMap][sizeMap], GLint maxRand, GLint smooth) {
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
  void static setTemperatureMap(GLfloat(&massMap)[sizeMap][sizeMap], GLint sizeX, GLint sizeY) {
    for (int i = 0; i < sizeX; i++)
      for (int j = 0; j < sizeY; j++)
        temperatureMap[i][j] = massMap[i][j];
  }
  void static setHumidityMap(GLfloat(&massMap)[sizeMap][sizeMap], GLint sizeX, GLint sizeY) {
    for (int i = 0; i < sizeX; i++)
      for (int j = 0; j < sizeY; j++)
        humidityMap[i][j] = massMap[i][j];
  }
};