#pragma once

#include "flowField.h"

class agent;

class steeringBehavior{
public:   
   void stayInArea(agent &agent, int turnPoint);
   void uniformFlow(agent &agent, flowField &flow);

};