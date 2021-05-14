#pragma once

#include "scenario.h"
#include "obstacle.h"
#include <vector>

using namespace std;

class obstacleAvoidance: public scenario{
public:
   obstacleAvoidance();
   static void loop(); 
   static vector<obstacle> obstacles;
   static void createObstacle(vector<obstacle> &obstacles); 
};

