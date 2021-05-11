#pragma once

#include <vector>
#include "point.h"
#include "graphics.h"

using namespace std;

class obstacle{
public:
   point p;
   float r;
   obstacle();      
   obstacle(point p, float r);
};
