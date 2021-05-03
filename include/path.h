#pragma once

#include "point.h"
#include <vector>

using namespace std;

class path{
public:
   vector<point> points;
   int width; 
   path(float width);
   path();
   void addPoint(point p);
   void createPath_1();
   void createPath_2();
};
