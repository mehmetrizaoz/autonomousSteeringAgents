#pragma once

#include <vector>

using namespace std;

class obstacle{
public:
   float x;
   float y;   
   float r;
   static void createObstacle();
   static void draw();
   obstacle(float x, float y, float r);
   static vector<obstacle> obstacles;  //TODO: move tocli,ent code    
};
