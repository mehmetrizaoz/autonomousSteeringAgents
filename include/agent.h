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
  pvector *getAcceleration();
  pvector *getPosition();
  pvector *getVelocity();
   
  pvector *calculateDirection(int x, int y);
  pvector *calculateNormal(pvector *v); //TODO: must be in pvector
  float    getMagnitude(pvector *v);    //TODO: must be in pvector
//private:
  pvector *direction;
  pvector *normal;
  pvector *acceleration;
  pvector *position;
  pvector *velocity;  
};

#endif