#pragma once

#include <vector>
#include "point.h"

using namespace std;

class obstacle{
public:
   point p;
   float r;
   obstacle();
   static void createObstacle();
   static void draw();
   obstacle(point p, float r);
   static vector<obstacle> obstacles;  //TODO: move tocli,ent code    
};
