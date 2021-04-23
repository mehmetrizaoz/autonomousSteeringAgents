#ifndef AGENT_H
#define AGENT_H

#include "pvector.h"
#include "point.h"
#include "flowField.h"
#include "graphics.h"

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
  void applySteeringForce();
  void applyWindForce(flowField &flow);
  void seekTarget();
  void reflect(graphics &view, int wall, int distance);
  void followSimplePath(graphics &view, path &pathSimple);
  void followMultiSegmentPath(graphics &view, path &pathMultiSegment);
  point   position;
  pvector velocity;  
  point   targetPoint;
private:
  pvector steering;
  pvector desired; //velocity
  pvector acceleration;
  pvector force;  
  float maxSpeed; 
  float maxForce;
  float r;
  float mass;
};

#endif