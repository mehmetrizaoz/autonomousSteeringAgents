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
  void limitVelocity();
  
  pvector *calculateDirection(int x, int y); //TODO: will be steer
  pvector *calculateNormal(pvector *v); //TODO: must be in pvector
  pvector *direction;
  pvector *normal;
  pvector *acceleration;
  pvector *position;
  pvector *velocity;  
};

#endif