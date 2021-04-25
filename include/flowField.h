#ifndef FLOW_FIELD_H
#define FLOW_FIELD_H

#include "pvector.h"

#define WIDTH       34
#define HEIGHT      34

#define WIND_WEST 1.0,  0.0
#define GRAVITY   0.0, -1.0

class flowField{
public:
   flowField(pvector p);
   flowField();
   pvector getField(int x, int y);
private:   
   void uniformVectorField(pvector p);
   void perlinNoise();
   void randomField();
   pvector uniformField[WIDTH][HEIGHT];
};

#endif
