#ifndef AGENT_H
#define AGENT_H

#include "pvector.h"
#include "point.h"
#include "flowField.h"
#include "graphics.h"
#include <vector>

using namespace std;

#define SEEK           1 
#define REFLECT        2
#define FLOW_FIELD     3
#define PATH_SIMPLE    4
#define PATH_COMPLEX   5
#define SEPARATION     6

class graphics;
class path;

class agent{
public:
  agent(float x, float y);
  ~agent();
  void updatePosition();
  void setMaxSpeed(float s);
  void setR(float s);
  void setMass(float m);
  void setMaxForce(float f);
  void applyForce();
  void setFeatures(float s, float f, float r, float m);
  //TODO: a new class will be created for agent behaviors 
  void addSteeringForce();
  void addFlowForce(flowField &flow);
  void addReflectionForce(graphics &view, int wall, int distance);
  void addTargetSeekForce();
  void addSeparationForce(vector<agent> agents);
  void followSimplePath(graphics &view, path &pathSimple);
  void followMultiSegmentPath(graphics &view, path &pathMultiSegment);
  point   position;
  pvector velocity;  
  point   targetPoint;
  float maxSpeed; 
  float maxForce;
  pvector steering;
private:
  pvector desiredVelocity;
  pvector acceleration;
  pvector force;  
  float r;
  float mass;
};

#endif