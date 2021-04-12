#ifndef AGENT_H
#define AGENT_H

#include "pvector.h"

class agent{
public:
  agent(float x, float y);
  void setAcceleration(float x, float y);
  void setVelocity(float x, float y);
  void setPosition(float x, float y);
  pvector *getAcceleration();
  pvector *getPosition();
  pvector *getVelocity();
  float getMagnitude(pvector *v);
//private:
  pvector *acceleration;
  pvector *position;
  pvector *velocity;  
};

#endif