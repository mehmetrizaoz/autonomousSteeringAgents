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
   static void createObstacle();
   static void draw(graphics view);
   obstacle(point p, float r);
   static vector<obstacle> obstacles;  //TODO: move tocli,ent code    
};
