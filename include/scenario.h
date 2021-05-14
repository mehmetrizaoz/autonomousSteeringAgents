#pragma once

#include "agent.h"
#include "graphics.h"
#include "steeringBehavior.h"
#include <vector>

using namespace std;

enum types{ RANDOM=0, STATIC, TROOP };

class scenario{
public:
   scenario();   
   void createAgent(int type, int count, const float force, const float speed);
   virtual void initGL(int * argv, char** argc)=0;

   static void refresh(); //opengl callback forces these static
   static vector<agent> agents;
   static graphics  view;
   static steeringBehavior behavior;
   static color myColor;   
   static string name;
private:
   void createRandomAgents(int agentCount, const float mForce, const float mSpeed);      
   void createStaticAgents();
   void createTroop(int agentCount);
};
