#ifndef AGENT_H
#define AGENT_H

#include "pvector.h"

class agent{
public:  
  ~agent();
  void setMaxSpeed(float s);
  void setR(float s);
  void setMass(float m);
  void setMaxForce(float f);
  void applyForce();
  void updatePosition();

  agent(float x, float y, float s, float f, float r, float m);
  pvector steering;
  pvector desired;
  pvector acceleration;
  pvector position;
  pvector velocity;  
  float maxSpeed; 
  float maxForce;
  float r;
  float mass;
};

#endif