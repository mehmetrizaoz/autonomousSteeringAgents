#ifndef POINT_H
#define POINT_H

#include "pvector.h"

class point{
public:
   float x;
   float y;   
   point(float x, float y);
   point();
   void div(float d);
   point operator + (pvector const &obj);
   point operator + (point const &obj);   
   pvector operator - (point const &obj);
   static point getNormalPoint(point predicted, point start, point end);
};

#endif
