#ifndef AGENT_H
#define AGENT_H

#include "pvector.h"

class agent{
public:
  agent(float x, float y);
  ~agent();
  
  void setMaxSpeed(float s);
  void setR(float s);
  void setMass(float m);
  void setMaxForce(float f);
  void applyForce();
  void setFeatures(float s, float f, float r, float m);
  pvector steering;
  pvector desired;
  pvector acceleration;
  pvector position;
  pvector velocity;  
  pvector force;  
  float maxSpeed; 
  float maxForce;
  float r;
  float mass;
};

#endif