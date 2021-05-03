#pragma once

#include "pvector.h"

#define WIDTH       34
#define HEIGHT      34

#define WIND_WEST 0.1,  0.0
#define GRAVITY   0.0, -0.1

class flowField{
public:
   flowField(pvector p);
   flowField();
   pvector getField(int x, int y);
  // static void createRandomArray(int *arr, int size);   
private:   
   void uniformVectorField(pvector p);
   void perlinNoise();
   void randomField();
   pvector uniformField[WIDTH][HEIGHT];
};
