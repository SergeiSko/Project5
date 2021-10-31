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
#include <GL\glut.h>

//#pragma warning(disable : 4996)

using namespace std;
using namespace chrono;

//GLshort const sizeMap = 5000;

const int sizeMass = 5000;

const static GLfloat colorBiom[12][3] = { //красный синий зеленый
{1.f, 0.f, 1.f}, //пустыня - желтый
{1.f, 1.f, 0.f}, //саванна - розовый
{0.f, 1.f, 1.f}, // сезонный лес - берюзовый 
{0.f, 1.f, 0.f}, //дождливый лес - синий
{0.f, 0.5f, 0.5f}, //болото - темно берюзовый
{0.f, 0.f, 1.f}, //лес - зеленый
{1.f, 0.6f, 0.f}, //деревья - оранжевый
{0.f, 0.f, 0.5f}, //тайга - темно синй
{1.f, 0.f, 0.f}, //равнина - красный
{0.5f, 0.f, 0.f}, //тундра - темно красный
{0.f, 0.f, 0.f}, //черный - 
{1.f, 1.f, 1.f} }; //белый - 