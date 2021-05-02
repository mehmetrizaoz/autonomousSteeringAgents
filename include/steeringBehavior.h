#pragma once

#include "flowField.h"
#include <vector>

#define FOLLOW_MOUSE   1 
#define STAY_IN_FIELD  2
#define IN_FLOW_FIELD  3
#define STAY_IN_PATH   4
#define STAY_IN_PATH_2 5
#define FLOCK          6
#define WANDER         7
#define PURSUIT        8
#define HIDE           9
#define PATH_LOOP      10

using namespace  std;

class agent;
class path;

class steeringBehavior{
public:   
   void stayInArea(agent &agent, int turnPoint);
   void inFlowField(agent &agent, flowField &flow);
   void stayInPath(agent &agent, path &path);
   void stayInPath_2(agent &agent, path &path); 
   void seek(agent &agent, bool arriving);
   void separation(vector<agent> agents, agent &agent, float multiplier);
   void cohesion(vector<agent> boids, agent &agent, float multiplier);
   void align(vector<agent> boids, agent &agent, float multiplier);
   void addSteeringForce(agent &agent, float multiplier);
   void wander(vector<agent> &agents);
   void setAngle(pvector &p, float angle);

};