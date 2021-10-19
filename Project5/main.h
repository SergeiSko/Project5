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

const static GLfloat colorBiom[12][3] = { {1.f, 1.f, 0.f}, {0.4f, 0.4f, 0.1f}, {0.f, 0.7f, 0.f}, 
{0.f, 0.8f, 0.f}, {0.f, 0.5f, 0.f}, {0.f, 0.8f, 0.f},  {0.f, 1.f, 0.4f}, 
{0.f, 0.4f, 0.f}, {0.2f, 1.f, 0.2f}, {0.f, 0.3f, 0.f}, {0.f, 0.f, 0.f}, {1.f, 1.f, 1.f} };