#ifndef FLOW_FIELD_H
#define FLOW_FIELD_H

#include "pvector.h"

#define WIDTH       34
#define HEIGHT      34

class flowField{
public:
   flowField();
   pvector getField(int x, int y);
private:   
   void uniformVectorField();
   void perlinNoise();
   void randomField();
   pvector field[WIDTH][HEIGHT];
};

#endif
