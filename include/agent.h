#ifndef AGENT_H
#define AGENT_H

#include "pvector.h"

class agent{
public:
  agent(float x, float y);
  void setAcceleration(float x, float y);
  void setVelocity(float x, float y);
  void setPosition(float x, float y);
  void setMaxSpeed(float s);
  void setR(float s);
  void setMass(float m);
  void setMaxForce(float f);
  pvector *steering;
  pvector *desired;
  pvector *acceleration;
  pvector *position;
  pvector *velocity;  
  float maxSpeed; 
  float maxForce;
  float r;
  float mass;
};

#endif