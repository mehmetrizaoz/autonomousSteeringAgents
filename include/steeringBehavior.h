#pragma once

#include "flowField.h"

class agent;
class path;

class steeringBehavior{
public:   
   void stayInArea(agent &agent, int turnPoint);
   void inFlowField(agent &agent, flowField &flow);
   void stayInPath(agent &agent, path &path);

};