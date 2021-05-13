#pragma once

#include "agent.h"
#include "graphics.h"
#include "steeringBehavior.h"
#include <vector>

using namespace std;

enum num{ RANDOM=0, STATIC, TROOP };

class scenario{
public:
   scenario();
   vector<agent> agents;
   void createAgent(int type);
   virtual void apply()=0;
   graphics  view;
   steeringBehavior behavior;
   color myColor;
private:
   void createRandomAgents(int agentCount, const float mForce, const float mSpeed);      
   void createStaticAgents();
   void createTroop(int agentCount);
};
