#ifndef AGENT_H
#define AGENT_H

#include "pvector.h"
#include "point.h"
#include "flowField.h"
#include "graphics.h"

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
  pvector steering;
  pvector desired; //velocity
  pvector acceleration;
  point   position;
  point   targetPoint;
  pvector velocity;  
  pvector force;  
  float maxSpeed; 
  float maxForce;
  float r;
  float mass;
};

#endif