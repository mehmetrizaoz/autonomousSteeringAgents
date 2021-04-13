#ifndef AGENT_H
#define AGENT_H

#include "pvector.h"

class agent{
public:
  agent(float x, float y);
  void setAcceleration(float x, float y);
  void setAcceleration(pvector *);
  void setVelocity(float x, float y);
  void setPosition(float x, float y);

  pvector *steering;
  pvector *desired;
  pvector *acceleration;
  pvector *position;
  pvector *velocity;  
  float maxSpeed; 
  float maxForce;
  float r;
};

#endif