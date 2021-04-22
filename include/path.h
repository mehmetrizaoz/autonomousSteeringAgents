#ifndef PATH_H
#define PATH_H

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
};

#endif
