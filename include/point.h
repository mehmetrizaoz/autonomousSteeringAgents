#ifndef POINT_H
#define POINT_H

#include "pvector.h"

class point{
public:
   float x;
   float y;   
   point(float x, float y);
   point();
   point   operator + (pvector const &obj);
   pvector operator - (point const &obj);
};

#endif
