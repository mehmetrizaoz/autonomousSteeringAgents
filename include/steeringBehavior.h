#pragma once

#include "flowField.h"

#define FOLLOW_MOUSE   1 
#define STAY_IN_FIELD  2
#define IN_FLOW_FIELD  3
#define STAY_IN_PATH   4
#define STAY_IN_PATH_2 5
#define FLOCK          6
#define PURSUIT        7
#define HIDE           8
#define PATH_LOOP      9

class agent;
class path;

class steeringBehavior{
public:   
   void stayInArea(agent &agent, int turnPoint);
   void inFlowField(agent &agent, flowField &flow);
   void stayInPath(agent &agent, path &path);
   void stayInPath_2(agent &agent, path &path); 

};