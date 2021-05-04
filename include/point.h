#pragma once

#include "pvector.h"
#include <string>

using namespace std;

class point{
public:
   float x;
   float y;   
   point(float x, float y);
   point();
   void div(float d);
   void print(const string &s);
   point   operator + (pvector const &obj);
   point   operator + (point const &obj);   
   pvector operator - (point const &obj);
   static point getNormalPoint(point predicted, point start, point end);
};
