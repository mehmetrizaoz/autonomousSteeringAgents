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
   void createAgent(int type, int count, float force, float speed);
   virtual void initGL(int * argv, char** argc)=0;

   static void refresh(); //opengl callback forces these static
   static vector<agent> agents;
   static graphics  view;
   static steeringBehavior behavior;
   static color myColor;   
   static string name;
   void (*callback)(); 
private:
   void createRandomAgents(int agentCount, float mForce, float mSpeed);      
   void createStaticAgents();
   void createTroop(int agentCount);
};
